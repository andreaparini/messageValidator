/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   validator.cc
 * Author: a.parini
 * 
 * Created on 21 gennaio 2019, 15.23
 */

#include "validator.h"

using rulesOption = vector < pair<string, const FieldDescriptor*> > ;

Validator::Validator() {};


Validator::~Validator() {};


bool Validator::validate (const Message& msgToValidate) {
    
    const Descriptor* descriptor = msgToValidate.GetDescriptor();
    const Reflection* reflection = msgToValidate.GetReflection();
    bool messageOK = true;
    
    
    for (unsigned int j = 0; j < descriptor->field_count(); j++) {
        
        const FieldDescriptor* fieldDescriptor = descriptor->field(j);
        
        rulesOption rulesVector = getOptionsValues(fieldDescriptor);
        
        if (rulesVector.size() > 0) {
            
            if (!checkMismatch(fieldDescriptor)){
            
                // check this field: find the value of the field
                const Message& fieldMessage = reflection->GetMessage(msgToValidate, fieldDescriptor);
                //const Descriptor* desc = fieldMessage.GetDescriptor();
                //int32_t fieldValue = fieldMessage.GetReflection()->GetInt32(fieldMessage, fieldMessage.GetDescriptor()->FindFieldByName("value"));

                for (unsigned int k = 0; k < rulesVector.size(); k++) {

                    if (!checkField(rulesVector[k].first, rulesVector[k].second, fieldMessage)) {
                        messageOK =  false;
                    }
                }
            } else {
                cout << "Constraint not allowed: skipped. Check warning for details" << endl;
            }
        } 
        
    }
    return messageOK;
  
};


bool Validator::canFieldHaveOptions (const FieldDescriptor* fieldDescriptor) {
   
    if( fieldDescriptor->type() == FieldDescriptor::Type::TYPE_MESSAGE ) {
        const Descriptor* descriptor = fieldDescriptor->message_type();
        if (descriptor->field_count() == 1) {
            const FieldDescriptor* valueFieldDescriptor = descriptor->field(0);
            if ( valueFieldDescriptor->type() == FieldDescriptor::Type::TYPE_FLOAT ) {
                return true;
            } else if ( valueFieldDescriptor->type() == FieldDescriptor::Type::TYPE_DOUBLE ) {
                return true;
            } else if ( valueFieldDescriptor->type() == FieldDescriptor::Type::TYPE_INT32 ) {
                return true;
            } else if ( valueFieldDescriptor->type() == FieldDescriptor::Type::TYPE_INT64 ) {
                return true;
            } else if ( valueFieldDescriptor->type() == FieldDescriptor::Type::TYPE_UINT32 ) {
                return true;
            } else if ( valueFieldDescriptor->type() == FieldDescriptor::Type::TYPE_UINT64 ) {
                return true;
            }
        }
    } 
    return false;  
    
};

bool Validator::checkMismatch (const FieldDescriptor* fieldDescriptor) {
    bool ret = false;
    
    const Descriptor* descriptor = fieldDescriptor->message_type();
    const FieldDescriptor* valueFieldDescriptor = descriptor->field(0);
    
    
    if (fieldDescriptor->options().GetExtension(validate::rules).has_floatrules() &&
            valueFieldDescriptor->type() != FieldDescriptor::Type::TYPE_FLOAT) {
        cout << "WARNING: your field has floatrules options, which are not compatible with your field value type. "
                "The option will be ignored" << endl;
        ret = true;
    }
    if (fieldDescriptor->options().GetExtension(validate::rules).has_doublerules() &&
            valueFieldDescriptor->type() != FieldDescriptor::Type::TYPE_DOUBLE) {
        cout << "WARNING: your field has doublerules options, which are not compatible with your field value type. "
                "The option will be ignored" << endl;
        ret = true;
    }
    if (fieldDescriptor->options().GetExtension(validate::rules).has_int32rules() &&
            valueFieldDescriptor->type() != FieldDescriptor::Type::TYPE_INT32) {
        cout << "WARNING: your field has int32rules options, which are not compatible with your field value type. "
                "The option will be ignored" << endl;
        ret = true;
    }
    if (fieldDescriptor->options().GetExtension(validate::rules).has_int64rules() &&
            valueFieldDescriptor->type() != FieldDescriptor::Type::TYPE_INT64) {
        cout << "WARNING: your field has int64rules options, which are not compatible with your field value type. "
                "The option will be ignored" << endl;
        ret = true;
    }
    if (fieldDescriptor->options().GetExtension(validate::rules).has_uint32rules() &&
            valueFieldDescriptor->type() != FieldDescriptor::Type::TYPE_UINT32) {
        cout << "WARNING: your field has uint32rules options, which are not compatible with your field value type. "
                "The option will be ignored" << endl;
        ret = true;
    }
    if (fieldDescriptor->options().GetExtension(validate::rules).has_uint64rules() &&
            valueFieldDescriptor->type() != FieldDescriptor::Type::TYPE_UINT64) {
        cout << "WARNING: your field has uint64rules options, which are not compatible with your field value type. "
                "The option will be ignored" << endl;
        ret = true;
    }
    
    return ret;
};


rulesOption Validator::getOptionsValues (const FieldDescriptor* fieldDescriptor) {
    
    rulesOption rulesVector;
    
    if(!canFieldHaveOptions(fieldDescriptor)) {
        return rulesVector;
    }
    
    if (fieldDescriptor->options().GetExtension(validate::rules).has_floatrules()) {
        if (fieldDescriptor->options().GetExtension(validate::rules).floatrules().has_equal()){
            string ruleName = "equal";
            //float_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).floatrules().equal().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).floatrules().has_lt()){
            string ruleName = "lt";
            //float_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).floatrules().lt().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).floatrules().has_lte()){
            string ruleName = "lte";
            //float_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).floatrules().lte().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).floatrules().has_gt()){
            string ruleName = "gt";
            //float_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).floatrules().gt().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).floatrules().has_gte()){
            string ruleName = "gte";
            //float_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).floatrules().gte().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
    }
    else if (fieldDescriptor->options().GetExtension(validate::rules).has_doublerules()) {
        if (fieldDescriptor->options().GetExtension(validate::rules).doublerules().has_equal()){
            string ruleName = "equal";
            //double_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).doublerules().equal().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).doublerules().has_lt()){
            string ruleName = "lt";
            //double_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).doublerules().lt().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).doublerules().has_lte()){
            string ruleName = "lte";
            //double_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).doublerules().lte().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).doublerules().has_gt()){
            string ruleName = "gt";
            //double_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).doublerules().gt().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).doublerules().has_gte()){
            string ruleName = "gte";
            //double_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).doublerules().gte().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
    } 
    else if (fieldDescriptor->options().GetExtension(validate::rules).has_int32rules()) {
        if (fieldDescriptor->options().GetExtension(validate::rules).int32rules().has_equal()){
            string ruleName = "equal";
            //int32_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).int32rules().equal().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).int32rules().has_lt()){
            string ruleName = "lt";
            //int32_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).int32rules().lt().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).int32rules().has_lte()){
            string ruleName = "lte";
            //int32_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).int32rules().lte().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).int32rules().has_gt()){
            string ruleName = "gt";
            //int32_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).int32rules().gt().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).int32rules().has_gte()){
            string ruleName = "gte";
            //int32_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).int32rules().gte().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
    } 
    else if (fieldDescriptor->options().GetExtension(validate::rules).has_int64rules()) {
        if (fieldDescriptor->options().GetExtension(validate::rules).int64rules().has_equal()){
            string ruleName = "equal";
            //int64_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).int64rules().equal().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).int64rules().has_lt()){
            string ruleName = "lt";
            //int64_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).int64rules().lt().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).int64rules().has_lte()){
            string ruleName = "lte";
            //int64_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).int64rules().lte().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).int64rules().has_gt()){
            string ruleName = "gt";
            //int64_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).int64rules().gt().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).int64rules().has_gte()){
            string ruleName = "gte";
            //int64_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).int64rules().gte().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
    } 
    else if (fieldDescriptor->options().GetExtension(validate::rules).has_uint32rules()) {
        if (fieldDescriptor->options().GetExtension(validate::rules).uint32rules().has_equal()){
            string ruleName = "equal";
            //uint32_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).uint32rules().equal().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).uint32rules().has_lt()){
            string ruleName = "lt";
            //uint32_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).uint32rules().lt().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).uint32rules().has_lte()){
            string ruleName = "lte";
            //uint32_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).uint32rules().lte().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).uint32rules().has_gt()){
            string ruleName = "gt";
            //uint32_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).uint32rules().gt().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).uint32rules().has_gte()){
            string ruleName = "gte";
            //uint32_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).uint32rules().gte().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
    } 
    else if (fieldDescriptor->options().GetExtension(validate::rules).has_uint64rules()) {
        if (fieldDescriptor->options().GetExtension(validate::rules).uint64rules().has_equal()){
            string ruleName = "equal";
            //uint64_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).uint64rules().equal().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).uint64rules().has_lt()){
            string ruleName = "lt";
            //uint64_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).uint64rules().lt().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).uint64rules().has_lte()){
            string ruleName = "lte";
            //uint64_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).uint64rules().lte().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).uint64rules().has_gt()){
            string ruleName = "gt";
            //uint64_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).uint64rules().gt().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).uint64rules().has_gte()){
            string ruleName = "gte";
            //uint64_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).uint64rules().gte().value();
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
    } 
    
    return rulesVector;
    
};


bool Validator::checkField(const string constraint, 
                           const FieldDescriptor* optionValueFieldDescriptor, 
                           const Message& valueFieldMessage)
{
        
    const Descriptor* descriptor = optionValueFieldDescriptor->message_type();
    const FieldDescriptor* valueFieldDescriptor = descriptor->field(0);

    if (valueFieldDescriptor->type() == FieldDescriptor::Type::TYPE_FLOAT) {

        float checkValue = valueFieldMessage.GetReflection()->GetFloat(valueFieldMessage, valueFieldMessage.GetDescriptor()->FindFieldByName("value"));

        if (constraint == "equal"){
            float optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).floatrules().equal().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "lt"){
            float optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).floatrules().lt().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "lte"){
            float optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).floatrules().lte().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "gt"){
            float optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).floatrules().gt().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "gte"){
            float optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).floatrules().gte().value();
            return check (constraint, checkValue, optionValue);
        }
    }
    else if (valueFieldDescriptor->type() == FieldDescriptor::Type::TYPE_DOUBLE) {

        double checkValue = valueFieldMessage.GetReflection()->GetDouble(valueFieldMessage, valueFieldMessage.GetDescriptor()->FindFieldByName("value"));

        if (constraint == "equal"){
            double optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).doublerules().equal().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "lt"){
            double optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).doublerules().lt().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "lte"){
            double optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).doublerules().lte().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "gt"){
            double optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).doublerules().gt().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "gte"){
            double optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).doublerules().gte().value();
            return check (constraint, checkValue, optionValue);
        }
    }
    else if (valueFieldDescriptor->type() == FieldDescriptor::Type::TYPE_INT32) {

        int32_t checkValue = valueFieldMessage.GetReflection()->GetInt32(valueFieldMessage, valueFieldMessage.GetDescriptor()->FindFieldByName("value"));

        if (constraint == "equal"){
            int32_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).int32rules().equal().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "lt"){
            int32_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).int32rules().lt().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "lte"){
            int32_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).int32rules().lte().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "gt"){
            int32_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).int32rules().gt().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "gte"){
            int32_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).int32rules().gte().value();
            return check (constraint, checkValue, optionValue);
        }
    }
    else if (valueFieldDescriptor->type() == FieldDescriptor::Type::TYPE_INT64) {

        int64_t checkValue = valueFieldMessage.GetReflection()->GetInt64(valueFieldMessage, valueFieldMessage.GetDescriptor()->FindFieldByName("value"));

        if (constraint == "equal"){
            int64_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).int64rules().equal().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "lt"){
            int64_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).int64rules().lt().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "lte"){
            int64_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).int64rules().lte().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "gt"){
            int64_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).int64rules().gt().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "gte"){
            int64_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).int64rules().gte().value();
            return check (constraint, checkValue, optionValue);
        }
    }
    else if (valueFieldDescriptor->type() == FieldDescriptor::Type::TYPE_UINT32) {

        uint32_t checkValue = valueFieldMessage.GetReflection()->GetUInt32(valueFieldMessage, valueFieldMessage.GetDescriptor()->FindFieldByName("value"));

        if (constraint == "equal"){
            uint32_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).uint32rules().equal().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "lt"){
            uint32_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).uint32rules().lt().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "lte"){
            uint32_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).uint32rules().lte().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "gt"){
            uint32_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).uint32rules().gt().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "gte"){
            uint32_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).uint32rules().gte().value();
            return check (constraint, checkValue, optionValue);
        }
    }
    else if (valueFieldDescriptor->type() == FieldDescriptor::Type::TYPE_UINT64) {

        uint64_t checkValue = valueFieldMessage.GetReflection()->GetUInt64(valueFieldMessage, valueFieldMessage.GetDescriptor()->FindFieldByName("value"));

        if (constraint == "equal"){
            uint64_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).uint64rules().equal().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "lt"){
            uint64_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).uint64rules().lt().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "lte"){
            uint64_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).uint64rules().lte().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "gt"){
            uint64_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).uint64rules().gt().value();
            return check (constraint, checkValue, optionValue);
        }
        if (constraint == "gte"){
            uint64_t optionValue = optionValueFieldDescriptor->options().GetExtension(validate::rules).uint64rules().gte().value();
            return check (constraint, checkValue, optionValue);
        }
    }
    
    
};

template <typename T>
bool Validator::check (const string constraint, 
            const T checkValue, 
            const T optionValue) 
{
    std::unordered_map<std::type_index, std::string> type_names;
    
    type_names[std::type_index(typeid(float))] = "float";
    type_names[std::type_index(typeid(double))] = "double";
    type_names[std::type_index(typeid(int32_t))] = "int32_t";
    type_names[std::type_index(typeid(int64_t))] = "int64_t";
    type_names[std::type_index(typeid(uint32_t))] = "uint32_t";
    type_names[std::type_index(typeid(uint64_t))] = "uint64_t";
    
    
    if (constraint == "equal"){
        if (checkValue == optionValue) {
            cout << type_names[std::type_index(typeid(checkValue))];
            cout << " Rule check " << constraint << " succeeded: " << checkValue 
                    << " is " << constraint << " to " << optionValue
                    << endl;
            return true;
        } 
        else {
            cout << type_names[std::type_index(typeid(checkValue))];
            cout << " Rule check " << constraint << " failed: " << checkValue 
                    << " is not " << constraint << " to " << optionValue
                    << endl;
            return false;
        }
    }
    if (constraint == "lt"){
        if (checkValue < optionValue) {
            cout << type_names[std::type_index(typeid(checkValue))];
            cout << " Rule check " << constraint << " succeeded: " << checkValue 
                    << " is " << constraint << " to " << optionValue
                    << endl;
            return true;
        } 
        else {
            cout << type_names[std::type_index(typeid(checkValue))];
            cout << " Rule check " << constraint << " failed: " << checkValue 
                    << " is not " << constraint << " to " << optionValue
                    << endl;
            return false;
        }
    }
    if (constraint == "lte"){
        if (checkValue <= optionValue) {
            cout << type_names[std::type_index(typeid(checkValue))];
            cout << " Rule check " << constraint << " succeeded: " << checkValue 
                    << " is " << constraint << " to " << optionValue
                    << endl;
            return true;
        } 
        else {
            cout << type_names[std::type_index(typeid(checkValue))];
            cout << " Rule check " << constraint << " failed: " << checkValue 
                    << " is not " << constraint << " to " << optionValue
                    << endl;
            return false;
        }
    }
    if (constraint == "gt"){
        if (checkValue > optionValue) {
            cout << type_names[std::type_index(typeid(checkValue))];
            cout << " Rule check " << constraint << " succeeded: " << checkValue 
                    << " is " << constraint << " to " << optionValue
                    << endl;
            return true;
        } 
        else {
            cout << type_names[std::type_index(typeid(checkValue))];
            cout << " Rule check " << constraint << " failed: " << checkValue 
                    << " is not " << constraint << " to " << optionValue
                    << endl;
            return false;
        }
    }
    if (constraint == "gte"){
        if (checkValue >= optionValue) {
            cout << type_names[std::type_index(typeid(checkValue))];
            cout << " Rule check " << constraint << " succeeded: " << checkValue 
                    << " is " << constraint << " to " << optionValue
                    << endl;
            return true;
        } 
        else {
            cout << type_names[std::type_index(typeid(checkValue))];
            cout << " Rule check " << constraint << " failed: " << checkValue 
                    << " is not " << constraint << " to " << optionValue
                    << endl;
            return false;
        }
    }
    
}