/*
 * Copyright 2017 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <Foundation/Foundation.h>

#include <memory>

#import "Firestore/Source/API/objc_user_data_converter.h"

#include "Firestore/core/src/firebase/firestore/core/user_data.h"
#include "Firestore/core/src/firebase/firestore/model/database_id.h"

@class FSTObjectValue;
@class FSTFieldValue;
@class FSTMutation;

namespace api = firebase::firestore::api;
namespace core = firebase::firestore::core;
namespace model = firebase::firestore::model;

NS_ASSUME_NONNULL_BEGIN

/**
 * Helper for parsing raw user input (provided via the API) into internal model classes.
 */
@interface FSTUserDataConverter : NSObject

- (instancetype)initWithConverter:(std::shared_ptr<api::ObjcUserDataConverter>)converter
    NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithDatabaseID:(model::DatabaseId)databaseID;
- (instancetype)init NS_UNAVAILABLE;

- (const model::DatabaseId &)databaseID;

/** Parse document data from a non-merge setData call.*/
- (core::ParsedSetData)parsedSetData:(id)input;

/** Parse document data from a setData call with `merge:YES`. */
- (core::ParsedSetData)parsedMergeData:(id)input fieldMask:(nullable NSArray<id> *)fieldMask;

/** Parse update data from an updateData call. */
- (core::ParsedUpdateData)parsedUpdateData:(id)input;

/** Parse a "query value" (e.g. value in a where filter or a value in a cursor bound). */
- (FSTFieldValue *)parsedQueryValue:(id)input;

@end

NS_ASSUME_NONNULL_END
