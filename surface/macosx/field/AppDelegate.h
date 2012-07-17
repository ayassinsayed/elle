//
//  OOAppDelegate.h
//  Infinit
//
//  Created by Charles Guillot - Infinit on 3/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
    NSWindow *window;
    IBOutlet NSMenu *statusMenu;
    IBOutlet NSMenu *statusLoginMenu;
    NSStatusItem *statusItem;
    NSInteger currentFrame;
    NSTimer *animTimer;
    int     pendingCount;
    BOOL     isPending;
}

@property(assign)   IBOutlet NSWindow   *window;
@property(assign)   NSInteger           currentFrame;
@property(assign)   NSTimer             *animTimer;
@property           BOOL                isPending;

- (void)launch8infinit;

- (void)addPending;
- (void)removePending;
- (void)updateStatusItemImageWithTimer:(NSTimer*)arg1;

- (IBAction)openInfinitNeworks:(id)sender;
- (IBAction)installInjectBundle:(id)sender;
- (IBAction)injectBundle:(id)sender;
- (IBAction)launchWebsite:(id)sender;
- (IBAction)launchHelpCenter:(id)sender;

- (void)updateProgessChangedNotification:(NSNotification *)notification;

@end
