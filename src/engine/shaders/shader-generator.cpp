#include <shaders/nodes/inline-shader-node.hpp>
#include <shaders/nodes/call-shader-node.hpp>
#include "shader-generator.hpp"

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

  // Cleans every allocated nodes
  for (auto& nodeVist : nodes_)
  {
    auto& nodePtr = nodeVist.first;
    if (nodePtr != nullptr)
      delete nodePtr;
  }

  return fragmentStack_;
}

void
ShaderGenerator::include(std::string text)
{
  includeStack_.push_back(text);
}

VariableShaderNode*
ShaderGenerator::createVariable(std::string type,
                                std::string name,
                                std::string prefix)
{
  auto elt = variablesMap_.find(name);
  if (elt != variablesMap_.end())
    return elt->second;

  auto var = createNode<VariableShaderNode>();
  var->setType(type);
  var->setName(name);
  var->setPrefix(prefix);

  variablesMap_[name] = var;
  return var;
}

UniformShaderNode*
ShaderGenerator::requestUniform(std::string type,
                                std::string name,
                                std::string defaultValue)
{
  auto elt = uniformMap_.find(name);
  if (elt != uniformMap_.end())
    return elt->second;

  auto uniformNode = createNode<UniformShaderNode>();
  uniformNode->setType(type);
  uniformNode->setName(name);
  uniformNode->setDefaultValue(defaultValue);

  uniformMap_[name] = uniformNode;

  return uniformNode;
}

ShaderNode*
ShaderGenerator::generateFragmentShaderGraph()
{
  auto alphavar = this->createVariable("vec4", "alpha", "const");
  auto integer = this->createVariable("int", "integer");
  this->createVariable("vec4", "vec");

  this->requestUniform("vec2", "positionUniform", "vec2(1.0f, 0.0f)");

  std::string alphaInline = "${output0} = ${input0} * ${input1};";
  auto node = createNode<InlineShaderNode>()->text(alphaInline)
              ->input(integer)->input(integer)
              ->output(integer);

  auto callNode = createNode<CallShaderNode>()->setName("clamp")
                  ->setReturnType("vec4")
                  ->input(alphavar)->input(integer);

  this->include("function test(in vec4 a) {\n  \ttest \n}");

  return callNode;
}

void ShaderGenerator::traverse(ShaderNode* node)
{
  if (nodes_[node])
    return;
  nodes_[node] = true;

  for (auto input : node->getInputs())
    traverse(input);

  if (dynamic_cast<VariableShaderNode*>(node) == nullptr)
    fragmentStack_.push_back("\t" + node->toString() + "\n");
}