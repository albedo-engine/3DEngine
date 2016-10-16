#include <shaders/nodes/inline-shader-node.hpp>
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

  fragmentStack_.push_back("}");

  // Cleans every allocated nodes
  for (auto& nodePtr : nodes_)
  {
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
}

ShaderNode*
ShaderGenerator::generateFragmentShaderGraph()
{
  this->createVariable("vec4", "alpha");
  this->createVariable("int", "lama");
  this->createVariable("vec4", "lol");


  auto node = createNode<InlineShaderNode>();
  return node;
}