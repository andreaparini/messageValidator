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


vector<Validator::ValidationOutput> Validator::validate (const Message& msgToValidate) {
    
    const Descriptor* descriptor = msgToValidate.GetDescriptor();
    const Reflection* reflection = msgToValidate.GetReflection();
    vector<Validator::ValidationOutput> validationStatus;
    
    
    for (unsigned int j = 0; j < descriptor->field_count(); j++) {
        const FieldDescriptor* fieldDescriptor = descriptor->field(j);
        
        rulesOption rulesVector = getOptionsValues(fieldDescriptor);
        if (rulesVector.size() > 0) {
            
            if (!checkMismatch(fieldDescriptor)){
            
                // check this field: find the value of the field
                const Message& fieldMessage = reflection->GetMessage(msgToValidate, fieldDescriptor);
                //const Descriptor* desc = fieldMessage.GetDescriptor();
                //int32_t fieldValue = fieldMessage.GetReflection()->GetInt32(fieldMessage, fieldMessage.GetDescriptor()->FindFieldByName("value"));
                bool validated = true;
                for (unsigned int k = 0; k < rulesVector.size(); k++) {
                    
                    if (!checkField(rulesVector[k].first, rulesVector[k].second, fieldMessage)) {
                        validated = false; 
                    }
                }
                if (validated) {
                        validationStatus.push_back(VALIDATED);
                    } else {
                        validationStatus.push_back(NOT_VALIDATED);
                    }
            } else {
                validationStatus.push_back(INPUT_ERRORS);
            }
        } else {
            validationStatus.push_back(NOTHING_TO_CHECK);
        }
        
    }
    return validationStatus;
  
};


bool Validator::canFieldHaveOptions (const FieldDescriptor* fieldDescriptor) {
   
    if( fieldDescriptor->type() == FieldDescriptor::Type::TYPE_MESSAGE ) {
        const Descriptor* descriptor = fieldDescriptor->message_type();
        if (descriptor->field_count() == 1) {
            const FieldDescriptor* valueFieldDescriptor = descriptor->field(0);
            if ( valueFieldDescriptor->type() == FieldDescriptor::Type::TYPE_DOUBLE ) {
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
    
    
    if (fieldDescriptor->options().GetExtension(validate::rules).has_doublerules() &&
            valueFieldDescriptor->type() != FieldDescriptor::Type::TYPE_DOUBLE) {
        ret = true;
    }
    if (fieldDescriptor->options().GetExtension(validate::rules).has_int32rules() &&
            valueFieldDescriptor->type() != FieldDescriptor::Type::TYPE_INT32) {
        ret = true;
    }
    if (fieldDescriptor->options().GetExtension(validate::rules).has_int64rules() &&
            valueFieldDescriptor->type() != FieldDescriptor::Type::TYPE_INT64) {
        ret = true;
    }
    if (fieldDescriptor->options().GetExtension(validate::rules).has_uint32rules() &&
            valueFieldDescriptor->type() != FieldDescriptor::Type::TYPE_UINT32) {
        ret = true;
    }
    if (fieldDescriptor->options().GetExtension(validate::rules).has_uint64rules() &&
            valueFieldDescriptor->type() != FieldDescriptor::Type::TYPE_UINT64) {
        ret = true;
    }
    
    return ret;
};


rulesOption Validator::getOptionsValues (const FieldDescriptor* fieldDescriptor) {
    
    rulesOption rulesVector;
    
    if(!canFieldHaveOptions(fieldDescriptor)) {
        return rulesVector;
    }
    
    if (fieldDescriptor->options().GetExtension(validate::rules).has_doublerules()) {
        if (fieldDescriptor->options().GetExtension(validate::rules).doublerules().has_equal()){
            string ruleName = "equal";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).doublerules().has_lt()){
            string ruleName = "lt";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).doublerules().has_lte()){
            string ruleName = "lte";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).doublerules().has_gt()){
            string ruleName = "gt";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).doublerules().has_gte()){
            string ruleName = "gte";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
    } 
    if (fieldDescriptor->options().GetExtension(validate::rules).has_int32rules()) {
        if (fieldDescriptor->options().GetExtension(validate::rules).int32rules().has_equal()){
            string ruleName = "equal";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).int32rules().has_lt()){
            string ruleName = "lt";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).int32rules().has_lte()){
            string ruleName = "lte";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).int32rules().has_gt()){
            string ruleName = "gt";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).int32rules().has_gte()){
            string ruleName = "gte";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
    } 
    if (fieldDescriptor->options().GetExtension(validate::rules).has_int64rules()) {
        if (fieldDescriptor->options().GetExtension(validate::rules).int64rules().has_equal()){
            string ruleName = "equal";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).int64rules().has_lt()){
            string ruleName = "lt";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).int64rules().has_lte()){
            string ruleName = "lte";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).int64rules().has_gt()){
            string ruleName = "gt";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).int64rules().has_gte()){
            string ruleName = "gte";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
    } 
    if (fieldDescriptor->options().GetExtension(validate::rules).has_uint32rules()) {
        if (fieldDescriptor->options().GetExtension(validate::rules).uint32rules().has_equal()){
            string ruleName = "equal";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).uint32rules().has_lt()){
            string ruleName = "lt";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).uint32rules().has_lte()){
            string ruleName = "lte";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).uint32rules().has_gt()){
            string ruleName = "gt";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).uint32rules().has_gte()){
            string ruleName = "gte";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
    } 
    if (fieldDescriptor->options().GetExtension(validate::rules).has_uint64rules()) {
        if (fieldDescriptor->options().GetExtension(validate::rules).uint64rules().has_equal()){
            string ruleName = "equal";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).uint64rules().has_lt()){
            string ruleName = "lt";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).uint64rules().has_lte()){
            string ruleName = "lte";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).uint64rules().has_gt()){
            string ruleName = "gt";
            rulesVector.emplace_back(ruleName,fieldDescriptor);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).uint64rules().has_gte()){
            string ruleName = "gte";
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

    if (valueFieldDescriptor->type() == FieldDescriptor::Type::TYPE_DOUBLE) {

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
    
    
    if (constraint == "equal"){
        if (checkValue == optionValue) {
            return true;
        } 
        else {
            return false;
        }
    }
    if (constraint == "lt"){
        if (checkValue < optionValue) {
            return true;
        } 
        else {
            return false;
        }
    }
    if (constraint == "lte"){
        if (checkValue <= optionValue) {
            return true;
        } 
        else {
            return false;
        }
    }
    if (constraint == "gt"){
        if (checkValue > optionValue) {
            return true;
        } 
        else {
            return false;
        }
    }
    if (constraint == "gte"){
        if (checkValue >= optionValue) {
            return true;
        } 
        else {
            return false;
        }
    }
    
}