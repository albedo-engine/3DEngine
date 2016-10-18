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

  fragmentStack_.push_back("void main()\n{\n");

  // Creates all required variable at
  // the beginning of the main function
  fragmentStack_.push_back("\t// VARIABLE DECLARATION\n");
  for (auto vIt = variablesMap_.begin(); vIt != variablesMap_.end(); ++vIt)
  {
    auto& var = vIt->second;
    fragmentStack_.push_back("\t" + var->getType() + " " + var->getName() + ";\n");
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

VariableShaderNode*
ShaderGenerator::createVariable(std::string type, std::string name)
{
  auto var = createNode<VariableShaderNode>();
  var->setType(type);
  var->setName(name);

  variablesMap_[name] = var;
  return var;
}

ShaderNode*
ShaderGenerator::generateFragmentShaderGraph()
{
  auto alphavar = this->createVariable("vec4", "alpha");
  auto integer = this->createVariable("int", "integer");
  this->createVariable("vec4", "lol");

  std::string alphaInline = "${output0} = ${input0} * ${input1};";
  auto node = createNode<InlineShaderNode>()->text(alphaInline)
              ->input(integer)->input(integer)
              ->output(integer);

  auto callNode = createNode<CallShaderNode>()->setName("clamp")
                  ->setReturnType("vec4")
                  ->input(alphavar)->input(integer);

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