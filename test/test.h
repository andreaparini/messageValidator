/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test.h
 * Author: a.parini
 *
 * Created on 28 gennaio 2019, 12.27
 */

#ifndef TEST_H
#define TEST_H

#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <iostream>
#include <utility>
#include <vector>
#include <string>


#include "google/protobuf/wrappers.pb.h"
#include "../src/validator.h"

bool testMessage(const Message& message, 
                 const Validator::ValidationOutput expected);

bool test1_validation ();
bool test2_failures ();


#endif /* TEST_H */

