//
//  Copyright (c) 2017 Open Whisper Systems. All rights reserved.
//

#import "TSStorageKeys.h"
#import "YapDatabaseConnection+OWS.h"
#import <Foundation/Foundation.h>
#import <YapDatabase/YapDatabase.h>

@class ECKeyPair;
@class PreKeyRecord;
@class SignedPreKeyRecord;

NS_ASSUME_NONNULL_BEGIN

@interface TSStorageManager : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)sharedManager;

/**
 * Returns NO if:
 *
 * - Keychain is locked because device has just been restarted.
 * - Password could not be retrieved because of a keychain error.
 */
+ (BOOL)isDatabasePasswordAccessible;

/**
 * The safeBlockingMigrationsBlock block will
 * run any outstanding version migrations that are a) blocking and b) safe
 * to be run before the environment and storage is completely configured.
 *
 * Specifically, these migration should not depend on or affect the data
 * of any database view.
 */
- (void)setupDatabaseWithSafeBlockingMigrations:(void (^_Nonnull)())safeBlockingMigrationsBlock;

- (void)deleteThreadsAndMessages;
- (void)resetSignalStorage;

- (nullable YapDatabase *)database;
- (nullable YapDatabaseConnection *)newDatabaseConnection;

- (void)setObject:(id)object forKey:(NSString *)key inCollection:(NSString *)collection;
- (void)removeObjectForKey:(NSString *)string inCollection:(NSString *)collection;

- (BOOL)boolForKey:(NSString *)key inCollection:(NSString *)collection;
- (int)intForKey:(NSString *)key inCollection:(NSString *)collection;
- (void)setInt:(int)integer forKey:(NSString *)key inCollection:(NSString *)collection;
- (id)objectForKey:(NSString *)key inCollection:(NSString *)collection;
- (int)incrementIntForKey:(NSString *)key inCollection:(NSString *)collection;
- (nullable NSDate *)dateForKey:(NSString *)key inCollection:(NSString *)collection;
- (void)setDate:(NSDate *)value forKey:(NSString *)key inCollection:(NSString *)collection;
- (nullable NSDictionary *)dictionaryForKey:(NSString *)key inCollection:(NSString *)collection;
- (nullable NSString *)stringForKey:(NSString *)key inCollection:(NSString *)collection;
- (nullable NSData *)dataForKey:(NSString *)key inCollection:(NSString *)collection;
- (nullable ECKeyPair *)keyPairForKey:(NSString *)key inCollection:(NSString *)collection;
- (nullable PreKeyRecord *)preKeyRecordForKey:(NSString *)key inCollection:(NSString *)collection;
- (nullable SignedPreKeyRecord *)signedPreKeyRecordForKey:(NSString *)key inCollection:(NSString *)collection;
- (void)purgeCollection:(NSString *)collection;

@property (nullable, nonatomic, readonly) YapDatabaseConnection *dbReadConnection;
@property (nullable, nonatomic, readonly) YapDatabaseConnection *dbReadWriteConnection;

@end

NS_ASSUME_NONNULL_END
