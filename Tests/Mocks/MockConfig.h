#pragma once

#include <any>
#include <cstddef>

#include <Config/ConfigVariableTypes.h>

struct MockConfig {
    MOCK_METHOD(std::any, getVariable, (std::size_t configVariableTypeIndex));
    MOCK_METHOD(void, setVariable, (std::size_t configVariableTypeIndex, std::any value));
    MOCK_METHOD(void, setVariableWithoutAutoSave, (std::size_t configVariableTypeIndex, std::any value));

    template <typename ConfigVariable>
    [[nodiscard]] auto getVariable()
    {
        auto&& variable = getVariable(ConfigVariableTypes::indexOf<ConfigVariable>());
        if (variable.has_value())
            return std::any_cast<typename ConfigVariable::ValueType>(variable);
        return ConfigVariable::kDefaultValue;
    }

    template <typename ConfigVariable>
    void setVariableWithoutAutoSave(ConfigVariable::ValueType value)
    {
        setVariableWithoutAutoSave(ConfigVariableTypes::indexOf<ConfigVariable>(), value);
    }
};
