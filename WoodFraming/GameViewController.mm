//
//  GameViewController.m
//  WoodFraming
//
//  Created by Mateusz Bugaj on 15.08.2015.
//  Copyright (c) 2015 Ocean Planet Studios. All rights reserved.
//

//for testing



#include "iOS_wrapper.hxx"
#import "GameViewController.h"
#import <OpenGLES/ES2/glext.h>




@interface GameViewController () {
}
@property (strong, nonatomic) EAGLContext *context;


@end

@implementation GameViewController

- (void)glkViewController:(GLKViewController *)controller
                willPause:(BOOL)pause
{
    if(pause)
    {
        floppy::appPause();
    }else
    {
        floppy::appResume();
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context) {
        floppy::failedToCreateGLContext();
    }else
    {
    
        GLKView *view = (GLKView *)self.view;
        view.context = self.context;
        view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
        self.delegate=self;
        self.preferredFramesPerSecond=floppy::desiredFPS();
        

        floppy::startEngine();
    }
}

- (void)dealloc
{
    floppy::stopEngine();

    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        floppy::stopEngine();

        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)glkViewControllerUpdate:(GLKViewController *)controller
{
     floppy::everyFrameUpdate();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    floppy::drawCalls();
}



@end
