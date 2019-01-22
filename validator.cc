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
                const Descriptor* desc = fieldMessage.GetDescriptor();
                int32_t fieldValue = fieldMessage.GetReflection()->GetInt32(fieldMessage, desc->FindFieldByName("value"));

                for (unsigned int k = 0; k < rulesVector.size(); k++) {

                    if (!checkMessage(rulesVector[k].first, rulesVector[k].second, fieldValue)) {
                        messageOK =  false;
                    }
                }
            } else {
                cout << "Constraint not allowed: skipped. Check warning for details" << endl;
            }
        } //else cout << "Vector size = 0" << endl;// else nothing to check for this field
        
    }
    return messageOK;
  
};


bool Validator::canFieldHaveOptions (const FieldDescriptor* fieldDescriptor) {
   
    if( fieldDescriptor->type() == FieldDescriptor::Type::TYPE_MESSAGE ) {
        const Descriptor* descriptor = fieldDescriptor->message_type();
        if (descriptor->field_count() == 1) {
            const FieldDescriptor* valueFieldDescriptor = descriptor->field(0);
            if ( valueFieldDescriptor->type() == FieldDescriptor::Type::TYPE_INT32 ) {
                return true;
            }
        }
    } 
    return false;  
    
};

bool Validator::checkMismatch (const FieldDescriptor* fieldDescriptor) {
    bool ret = false;
    if (fieldDescriptor->options().GetExtension(validate::rules).has_floatrules()) {
        cout << "WARNING: your field has floatrules options which are not allowed with int32 type. "
                "The option will be ignored" << endl;
        ret = true;
    }
    if (fieldDescriptor->options().GetExtension(validate::rules).has_doublerules()) {
        cout << "WARNING: your field has doublerules options which are not allowed with int32 type. "
                "The option will be ignored" << endl;
        ret = true;
    }
    if (fieldDescriptor->options().GetExtension(validate::rules).has_int64rules()) {
        cout << "WARNING: your field has int64rules options which are not allowed with int32 type. "
                "The option will be ignored" << endl;
        ret = true;
    }
    if (fieldDescriptor->options().GetExtension(validate::rules).has_uint32rules()) {
        cout << "WARNING: your field has uint32rules options which are not allowed with int32 type. "
                "The option will be ignored" << endl;
        ret = true;
    }
    if (fieldDescriptor->options().GetExtension(validate::rules).has_uint64rules()) {
        cout << "WARNING: your field has uint64rules options which are not allowed with int32 type. "
                "The option will be ignored" << endl;
        ret = true;
    }
    if (fieldDescriptor->options().GetExtension(validate::rules).has_sint32rules()) {
        cout << "WARNING: your field has sint32rules options which are not allowed with int32 type. "
                "The option will be ignored" << endl;
        ret = true;
    }
    if (fieldDescriptor->options().GetExtension(validate::rules).has_sint64rules()) {
        cout << "WARNING: your field has sint64rules options which are not allowed with int32 type. "
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
    unsigned int size = 0;
    if (fieldDescriptor->options().GetExtension(validate::rules).has_int32rules()) {
        if (fieldDescriptor->options().GetExtension(validate::rules).int32rules().has_equal()){
            string ruleName = "equal";
            int32_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).int32rules().equal().value();
            rulesVector.emplace_back(ruleName,ruleValue);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).int32rules().has_lt()){
            string ruleName = "lt";
            int32_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).int32rules().lt().value();
            rulesVector.emplace_back(ruleName,ruleValue);
        } 
        if (fieldDescriptor->options().GetExtension(validate::rules).int32rules().has_lte()){
            string ruleName = "lte";
            int32_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).int32rules().lte().value();
            rulesVector.emplace_back(ruleName,ruleValue);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).int32rules().has_gt()){
            string ruleName = "gt";
            int32_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).int32rules().gt().value();
            rulesVector.emplace_back(ruleName,ruleValue);
        }
        if (fieldDescriptor->options().GetExtension(validate::rules).int32rules().has_gte()){
            string ruleName = "gte";
            int32_t ruleValue = fieldDescriptor->options().GetExtension(validate::rules).int32rules().gte().value();
            rulesVector.emplace_back(ruleName,ruleValue);
        }
    }
    return rulesVector;
    
};


bool Validator::checkMessage(const string constraint, int32_t optionValue, int32_t checkValue){
    
    if (constraint == "equal"){
        if (checkValue == optionValue) {
            cout << "Rule check " << constraint << " succeeded: " << checkValue 
                    << " is " << constraint << " to " << optionValue
                    << endl;
            return true;
        } else {
            cout << "Rule check " << constraint << " failed: " << checkValue 
                    << " is not " << constraint << " to " << optionValue
                    << endl;
            return false;
        }
    }
    if (constraint == "lt"){
        if (checkValue < optionValue) {
            cout << "Rule check " << constraint << " succeeded: " << checkValue 
                    << " is " << constraint << " to " << optionValue
                    << endl;
            return true;
        } else {
            cout << "Rule check " << constraint << " failed: " << checkValue 
                    << " is not " << constraint << " to " << optionValue
                    << endl;
            return false;
        }
    }
    if (constraint == "lte"){
        if (checkValue <= optionValue) {
            cout << "Rule check " << constraint << " succeeded: " << checkValue 
                    << " is " << constraint << " to " << optionValue
                    << endl;
            return true;
        } else {
            cout << "Rule check " << constraint << " failed: " << checkValue 
                    << " is not " << constraint << " to " << optionValue
                    << endl;
            return false;
        }
    }
    if (constraint == "gt"){
        if (checkValue > optionValue) {
            cout << "Rule check " << constraint << " succeeded: " << checkValue 
                    << " is " << constraint << " to " << optionValue
                    << endl;
            return true;
        } else {
            cout << "Rule check " << constraint << " failed: " << checkValue 
                    << " is not " << constraint << " to " << optionValue
                    << endl;
            return false;
        }
    }
    if (constraint == "gte"){
        if (checkValue >= optionValue) {
            cout << "Rule check " << constraint << " succeeded: " << checkValue 
                    << " is " << constraint << " to " << optionValue
                    << endl;
            return true;
        } else {
            cout << "Rule check " << constraint << " failed: " << checkValue 
                    << " is not " << constraint << " to " << optionValue
                    << endl;
            return false;
        }
    }

};

