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
//
//  ARSAL_CentralManager.h
//  ARFreeFlight
//
//  Created by Frédéric D'HAEYER on 12/03/14.
//  Copyright (c) 2014 Parrot SA. All rights reserved.
//
#import <CoreBluetooth/CoreBluetooth.h>

@interface ARSAL_CentralManager : NSObject

- (void)initARCBCentralManager:(dispatch_queue_t)queue options:(NSDictionary *)options;
- (id)initWithQueue:(dispatch_queue_t)queue;
- (id)initWithDelegate:(id<CBCentralManagerDelegate>)delegate queue:(dispatch_queue_t)queue options:(NSDictionary *)options;

- (void)addDelegate:(id <CBCentralManagerDelegate>)delegate;
- (void)removeDelegate:(id <CBCentralManagerDelegate>)delegate;

- (void)connectPeripheral:(CBPeripheral *)peripheral options:(NSDictionary *)options;
- (void)cancelPeripheralConnection:(CBPeripheral *)peripheral;
- (void)scanForPeripheralsWithServices:(NSArray *)serviceUUIDs options:(NSDictionary *)options;
- (void)stopScan;

- (NSArray *)retrieveConnectedPeripheralsWithServices:(NSArray *)serviceUUIDs;
- (NSArray *)retrievePeripheralsWithIdentifiers:(NSArray *)identifiers;

@end
