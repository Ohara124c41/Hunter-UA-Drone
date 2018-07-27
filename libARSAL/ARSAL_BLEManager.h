/*
    Copyright (C) 2014 Parrot SA

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the 
      distribution.
    * Neither the name of Parrot nor the names
      of its contributors may be used to endorse or promote products
      derived from this software without specific prior written
      permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
    OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
    AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
    OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
*/
/**
 * @file  ARSAL_BLEManager.h
 * @brief private headers of BLE manager allow to use Bluetooth low energy api's
 * @date 06/11/2013
 * @author frederic.dhaeyer@parrot.com
 */

#ifndef _ARSAL_BLEMANAGER_H_
#define _ARSAL_BLEMANAGER_H_

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#include "libARSAL/ARSAL_Print.h"
#include "libARSAL/ARSAL_Mutex.h"
#include "libARSAL/ARSAL_Sem.h"
#include "libARSAL/ARSAL_CentralManager.h"
#include "libARSAL/ARSAL_Error.h"
#include "ARSAL_Singleton.h"

@interface CBUUID (StringExtraction)
- (NSString *)representativeString;
- (NSString *)shortUUID;
@end

@interface ARSALBLEManagerNotificationData : NSObject

@property (nonatomic, retain) CBCharacteristic *characteristic;
@property (nonatomic, retain) NSData *value;
@end

@interface ARSALBLEManagerNotification : NSObject
{
    ARSAL_Sem_t readCharacteristicsSem;
    ARSAL_Mutex_t readCharacteristicMutex;
}
@property (nonatomic, retain) NSArray *characteristics;
@property (nonatomic, retain) NSMutableArray *notificationsArray;
@end

@protocol ARSALBLEManagerDelegate <NSObject>
@required
- (void)onBLEDisconnect;
@end

@interface ARSAL_BLEManager : NSObject <CBCentralManagerDelegate, CBPeripheralDelegate>
{
    ARSAL_Sem_t connectionSem;
    ARSAL_Sem_t disconnectionSem;
    ARSAL_Sem_t discoverServicesSem;
    ARSAL_Sem_t discoverCharacteristicsSem;
    ARSAL_Sem_t writeCharacteristicSem;

    ARSAL_Sem_t configurationSem;
}

@property (nonatomic, assign) id <ARSALBLEManagerDelegate> delegate;
@property (nonatomic, retain) CBPeripheral *activePeripheral;
@property (nonatomic, retain) NSMutableArray *characteristicsNotifications;

DECLARE_SINGLETON_FOR_CLASS(ARSAL_BLEManager);

- (eARSAL_ERROR)connectToPeripheral:(CBPeripheral *)peripheral withCentralManager:(ARSAL_CentralManager *)centralManager;
- (void)disconnectPeripheral:(CBPeripheral *)peripheral withCentralManager:(ARSAL_CentralManager *)centralManager;
- (eARSAL_ERROR)discoverNetworkServices:(NSArray *)servicesUUIDs;
- (eARSAL_ERROR)discoverNetworkCharacteristics:(NSArray *)characteristicsUUIDs forService:(CBService *)service;
- (eARSAL_ERROR)setNotificationCharacteristic:(CBCharacteristic *)characteristic;
- (BOOL)writeData:(NSData *)data toCharacteristic:(CBCharacteristic *)characteristic;
- (eARSAL_ERROR)writeDataWithResponse:(NSData *)data toCharacteristic:(CBCharacteristic *)characteristic;
- (BOOL)isPeripheralConnected;
- (void)registerNotificationCharacteristics:(NSArray *)characteristicsArray toKey:(NSString*)readCharacteristicsKey;
- (BOOL)unregisterNotificationCharacteristics:(NSString*)readCharacteristicsKey;
- (BOOL)cancelReadNotification:(NSString *)readCharacteristicsKey;
- (BOOL)resetReadNotification:(NSString *)readCharacteristicsKey;
- (eARSAL_ERROR)readNotificationData:(NSMutableArray *)notificationArray maxCount:(int)maxCount timeout:(NSNumber *)timeout toKey:(NSString *)readCharacteristicsKey;   
- (void)readData:(CBCharacteristic *)characteristic;
- (void)unlock;
- (void)reset;

@end

#endif /** _ARSAL_BLEMANAGER_H_ */

