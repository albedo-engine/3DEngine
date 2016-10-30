#include "shader-generator.hpp"

namespace Engine
{
  namespace Shader
  {

    ShaderGenerator::ShaderGenerator(std::string name)
                    : name_(name)
    { }

    ShaderGenerator::~ShaderGenerator()
    { }

    std::vector<std::string>
    ShaderGenerator::generateShader()
    {
      auto output = generateFragmentShaderGraph();
      if (output == nullptr)
        throw std::logic_error("ShaderGenerator: at least one output should be given");

      // Creates all user defined types
      // at the beginning of the file
      fragmentStack_.push_back("// STRUCTS DECLARATION\n");
      for (auto tIt = typeDecMap_.begin(); tIt != typeDecMap_.end(); ++tIt)
      {
        fragmentStack_.push_back("struct " + tIt->first + "\n");
        fragmentStack_.push_back("{\n");

        auto& fields = tIt->second->getFields();
        for (auto fIt = fields.begin(); fIt != fields.end(); fIt++)
          fragmentStack_.push_back("\t" + fIt->second + " " + fIt->first + ";\n");

        fragmentStack_.push_back("};\n");
      }
      fragmentStack_.push_back("// END STRUCTS DECLARATION\n\n");

      // Creates all required uniforms
      // at the beginning of the file
      fragmentStack_.push_back("// UNIFORMS DECLARATION\n");
      for (auto uIt = uniformMap_.begin(); uIt != uniformMap_.end(); ++uIt)
      {
        auto& u = uIt->second;
        fragmentStack_.push_back("uniform " + u->getType() + " " + u->getName());
        if (!u->getDefaultValue().empty())
          fragmentStack_.push_back(" = " + u->getDefaultValue() + ";");
        fragmentStack_.push_back("\n");
      }
      fragmentStack_.push_back("// END UNIFORMS DECLARATION\n\n");

      // Adds all include to the top of the file
      fragmentStack_.push_back("// INCLUDES\n");
      for (auto& text : includeStack_)
        fragmentStack_.push_back(text);
      fragmentStack_.push_back("\n// END INCLUDES\n\n");

      // Begins the main function
      // containing the shader logic
      fragmentStack_.push_back("void main()\n{\n");

      // Creates all required variable at
      // the beginning of the main function
      fragmentStack_.push_back("\t// VARIABLE DECLARATION\n");
      for (auto vIt = variablesMap_.begin(); vIt != variablesMap_.end(); ++vIt)
      {
        auto& var = vIt->second;
        fragmentStack_.push_back("\t");
        if (!var->getPrefix().empty())
          fragmentStack_.push_back(var->getPrefix() + " ");
        fragmentStack_.push_back(var->getType() + " " + var->getName() + ";\n");
      }
      fragmentStack_.push_back("\t// END VARIABLE DECLARATION\n");

      traverse(output);

      fragmentStack_.push_back("\n}");

      clean();

      return fragmentStack_;
    }

    ShaderNode*
    ShaderGenerator::generateFragmentShaderGraph()
    {
      // Declares the light structure
      auto t = declareStruct("Light")
        ->addField("position", "vec3")
        ->addField("color", "vec3");

      auto alphavar = this->createVariable("vec4", "alpha", "const");
      auto integer = this->createVariable("int", "integer");
      this->createVariable("vec4", "vec");

      this->requestUniform("vec2", "positionUniform", "vec2(1.0f, 0.0f)");

      std::string alphaInline = "${output0} = ${input0} * ${input1};";
      auto node = createNode<InlineNode>()->text(alphaInline)
                  ->input(integer)->input(integer)
                  ->output(integer);

      this->include("function test(in vec4 a) {\n  \ttest \n}");

      this->createNode<OperationNode>()
          ->setOperation(OperationNode::Operation::ADD)
          ->input(alphavar)->input(alphavar)->input(alphavar)
          ->output(integer);

      auto callNode = createNode<CallNode>()->setName("clamp")
        ->setReturnType("vec4")
        ->input(alphavar)->input(integer);

      return callNode;
    }

    void
    ShaderGenerator::include(std::string text)
    {
      includeStack_.push_back(text);
    }

    TypeDec*
    ShaderGenerator::declareStruct(std::string name)
    {
      auto elt = typeDecMap_.find(name);
      if (elt != typeDecMap_.end())
        throw std::logic_error("ShaderGenerator: you cannot declare twice "
                               " the same structure");

      TypeDec* type = new TypeDec(name);
      typeDecMap_[name] = type;

      return type;
    }

    UniformNode*
    ShaderGenerator::requestUniform(std::string type,
                                    std::string name,
                                    std::string defaultValue)
    {
      auto elt = uniformMap_.find(name);
      if (elt != uniformMap_.end())
        return elt->second;

      auto uniformNode = createNode<UniformNode>();
      uniformNode->setType(type);
      uniformNode->setName(name);
      uniformNode->setDefaultValue(defaultValue);

      uniformMap_[name] = uniformNode;

      return uniformNode;
    }

    VariableNode*
    ShaderGenerator::createVariable(std::string type,
                                    std::string name,
                                    std::string prefix)
    {
      auto elt = variablesMap_.find(name);
      if (elt != variablesMap_.end())
        return elt->second;

      // Checks that the requested variable has a primitive type
      auto typeDecElt = typeDecMap_.find(type);
      if (typeDecElt == typeDecMap_.end())
      {
        auto var = createNode<VariableNode>();
        var->setType(type);
        var->setName(name);
        var->setPrefix(prefix);
        variablesMap_[name] = var;

        return var;
      }

      std::unordered_map<std::string, VariableNode*> vars;
      auto& structFields = typeDecElt->second->getFields();
      for (auto fIt = structFields.begin(); fIt != structFields.end(); ++fIt)
      {
        /*auto varField = createNode<VariableNode>();
        auto varName = name + "." + fIt->first;
        varField->setType(fIt->second);
        varField->setName(fIt->first);

        vars[varName] = varField;*/

        auto varName = name + "." + fIt->first;
        auto varField = createVariable(fIt->second, varName);

        vars[fIt->first] = varField;
      }

      auto var = new StructVariableNode(vars);
      nodes_[var] = false;

      return var;
    }

    void
    ShaderGenerator::traverse(ShaderNode* node)
    {
      if (nodes_[node])
        return;
      nodes_[node] = true;

      for (auto input : node->getInputs())
        traverse(input);

      if (dynamic_cast<VariableNode*>(node) == nullptr)
        fragmentStack_.push_back("\t" + node->toString() + "\n");
    }


    void
    ShaderGenerator::clean()
    {
      // Cleans every allocated nodes
      for (auto& nodeVist : nodes_)
      {
        auto& nodePtr = nodeVist.first;
        if (nodePtr != nullptr)
          delete nodePtr;
      }

      // Cleans type declarations
      for (auto& tElt : typeDecMap_)
        delete tElt.second;

    }
  } // namespace Shader
} // namespace Engine