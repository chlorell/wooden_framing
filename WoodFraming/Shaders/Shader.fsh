//
//  Shader.fsh
//  WoodFraming
//
//  Created by Mateusz Bugaj on 15.08.2015.
//  Copyright (c) 2015 Ocean Planet Studios. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
