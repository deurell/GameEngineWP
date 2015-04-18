//
//  SceneRequest.h
//  GameEngine
//
//  Created by Mikael Deurell on 2012-10-01.
//
//

#pragma once

struct SceneRequest {    
    int Scene;
    SceneRequest(int sceneId) {
        Scene = sceneId;
    }
};