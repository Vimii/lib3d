#include "lib3d.h"

static void transition(l3Environment* env, int frame) {
    l3Object* obj = l3FindObject(env, "box");
    obj->theta_y += radians(360 / 100);
    obj->theta_x += radians(360 / 100);
    obj->theta_z += radians(360 / 100);
    obj->dx = 15 * cos(frame / 100.0 * 2 * PI + PI);
    obj->dz = 15 * sin(frame / 100.0 * 2 * PI + PI);

    l3Object* sphere = l3FindObject(env, "sphere");
    sphere->theta_y += radians(360 / 100);
    sphere->dy = 50 * fabs(sin(1.0 * frame / 5.0));
    sphere->dx = 15 * cos(frame / 100.0 * 2 * PI);
    sphere->dz = 15 * sin(frame / 100.0 * 2 * PI);

    // sphere->poligons[0]->textureRotate += radians(1);

    // env->camera.coordinate[0] = 400.0 / ((frame + 1) / 30.0) * cos(-(frame + 1) / 100.0 * 2 * PI);
    // env->camera.coordinate[1] = (frame + 1) / 3.0;
    // env->camera.coordinate[2] = 400.0 / ((frame + 1) / 30.0) * sin(-(frame + 1) / 100.0 * 2 * PI);
}

int scene_core(int argc, const char* argv[], l3Options* options) {
    l3Environment env;
    {
        l3RGB red = {255, 0, 0};
        l3RGB green = {0, 255, 0};
        l3RGB blue = {0, 0, 255};
        l3RGB white = {255, 255, 255};
        l3InitializeEnvironment(&env);
        env.w = options->w;
        env.h = options->h;
        env.outdir = options->outdir;

        // オブジェクト構築
        l3Object* _object = l3CreateObject();

        // テクスチャ読み込み
        l3Texture texture;
        l3Load2DTexture("assets/manbou.ppm", &texture);

        {
            int vs[] = {
                l3AddVertexToObject(_object, l3CreateVertex(5, 5, 5, &red)),
                l3AddVertexToObject(_object, l3CreateVertex(-5, -5, 5, &green)),
                l3AddVertexToObject(_object, l3CreateVertex(5, -5, -5, &blue)),
                l3AddVertexToObject(_object, l3CreateVertex(-5, 5, -5, &white)),
            };
            // 右回りが表、数字はオブジェクトごとの頂点のインデックス
            l3Poligon* poligons[] = {
                l3CreatePoligon(0, 2, 1),
                l3CreatePoligon(0, 3, 2),
                l3CreatePoligon(1, 2, 3),
                l3CreatePoligon(0, 1, 3),
            };

            poligons[0]->material = l3PoligonMaterialColor;
            poligons[0]->color.r = 150;
            poligons[1]->material = l3PoligonMaterialColor;
            poligons[1]->color.g = 150;
            poligons[2]->material = l3PoligonMaterialColor;
            poligons[2]->color.r = 255;
            poligons[2]->color.b = 255;
            poligons[2]->color.g = 255;
            poligons[3]->material = l3PoligonMaterialColor;
            poligons[3]->color.r = 150;
            poligons[3]->color.b = 150;
            poligons[0]->transparency = 0.1;
            // poligons[1]->transparency = 0.1;
            poligons[2]->transparency = 0.1;
            // poligons[3]->transparency = 0.1;
            poligons[0]->metalness[0] = poligons[1]->metalness[0] = poligons[2]->metalness[0] = poligons[3]->metalness[0] = 0.05;
            poligons[0]->metalness[1] = poligons[1]->metalness[1] = poligons[2]->metalness[1] = poligons[3]->metalness[1] = 0.05;
            poligons[0]->metalness[2] = poligons[1]->metalness[2] = poligons[2]->metalness[2] = poligons[3]->metalness[2] = 0.05;

            // テクスチャ読み込み・貼り付け
            for (int i = 0; i < 2; i++) {
                poligons[i]->textureType = l3TextureTypeTiled;
                poligons[i]->textureRepeatX = 10;
                poligons[i]->textureRepeatY = 10;
                poligons[i]->textureCoordinateSystem = l3CoordinateSystemLocal;
                poligons[i]->texture = &texture;
                // poligons[i]->lightType = l3LightTypePoint;
                // poligons[i]->lightIntensity = 0.4;
            }
            l3Mat32A texture_vertices = {0.5, 0, 0, 0.8, 1, 0.8};
            for (int i = 2; i < 4; i++) {
                l3SetUVTexturePoligon(poligons[i], &texture, texture_vertices);
            }

            l3SetPoligonsToObject(_object, sizeof(poligons) / sizeof(l3Poligon*), poligons);
            l3SetTransposeObject(_object, -15, 10, 0);
            l3SetScaleObject(_object, 2, 2, 2);
            l3AddObjectToEnvironment(&env, _object, "test");
        }
        l3Object* obj2 = l3CreateBox();
        {
            l3SetTransposeObject(obj2, 0, 0, 0);
            l3SetScaleObject(obj2, 10, 10, 10);
            // l3AddObjectToEnvironment(&env, obj2, "box1");
        }
        l3Object* obj5 = l3CreateBox();
        {
            l3SetTransposeObject(obj5, -20, 0, 0);
            l3SetScaleObject(obj5, 10, 10, 10);
            // l3AddObjectToEnvironment(&env, obj5, "box2");
        }
        l3Object* obj4 = l3CreateBox();
        {
            l3SetTransposeObject(obj4, 20, 0, 0);
            l3SetScaleObject(obj4, 10, 10, 10);
            // l3AddObjectToEnvironment(&env, obj4, "boxddd3");
        }
        l3Object* column = l3CreateObject();
        {
            int vs[] = {
                l3AddVertexToObject(column, l3CreateVertex(0, 0, 0, &red)),
                l3AddVertexToObject(column, l3CreateVertex(0, 20, 0, &red)),
            };
            l3Poligon* poligons[] = {
                l3CreatePoligonColumn(0, 1, 10),
            };
            poligons[0]->color.r = 255;
            poligons[0]->color.g = 250;
            poligons[0]->color.b = 50;
            poligons[0]->material = l3PoligonMaterialColor;

            l3SetPoligonsToObject(column, sizeof(poligons) / sizeof(l3Poligon*), poligons);
            l3SetTransposeObject(column, 0, 0, 0);
            // l3AddObjectToEnvironment(&env, column, "column");
        }
        l3Texture texture2;
        l3Load2DTexture("assets/star.ppm", &texture2);

        l3Object* sphere = l3CreateObject();
        {
            int vs[] = {
                l3AddVertexToObject(sphere, l3CreateVertex(0, 0, 0, &red)),
                l3AddVertexToObject(sphere, l3CreateVertex(0, 10, 0, &red)),
            };
            l3Poligon* poligons[] = {
                l3CreatePoligonSphere(0, 1, 10),
            };
            poligons[0]->color.r = 255;
            poligons[0]->color.g = 50;
            poligons[0]->color.b = 50;
            poligons[0]->lightColor.r = 255;
            poligons[0]->lightColor.g = 50;
            poligons[0]->lightColor.b = 50;
            poligons[0]->material = l3PoligonMaterialColor;
            poligons[0]->lightType = l3LightTypePoint;
            poligons[0]->lightIntensity = 3;
            // poligons[0]->transparency = 0.5;
            poligons[0]->lightAttenuation = 0.004;
            // l3Mat32A texture_vertices = {0.5, 0.5, 0, 1, 1, 1};
            // poligons[0]->textureType = l3TextureTypeTiled;
            // poligons[0]->textureRepeatX = 10;
            // poligons[0]->textureRepeatY = 10;
            // poligons[0]->textureCoordinateSystem = l3CoordinateSystemLocal;
            // poligons[0]->texture = &texture2;
            // poligons[0]->normal[0] = 0;
            // poligons[0]->normal[1] = 1;
            // poligons[0]->normal[2] = 0;

            l3SetPoligonsToObject(sphere, sizeof(poligons) / sizeof(l3Poligon*), poligons);
            l3SetTransposeObject(sphere, 15, 0, 0);
            l3AddObjectToEnvironment(&env, sphere, "sphere");
        }
        l3Object* sphere2 = l3CreateObject();
        {
            int vs[] = {
                l3AddVertexToObject(sphere2, l3CreateVertex(0, 0, 0, &red)),
                l3AddVertexToObject(sphere2, l3CreateVertex(0, 5, 0, &red)),
            };
            l3Poligon* poligons[] = {
                l3CreatePoligonSphere(0, 1, 10),
            };
            poligons[0]->material = l3PoligonMaterialColor;
            poligons[0]->color = white;
            poligons[0]->lightColor = white;
            poligons[0]->lightType = l3LightTypePoint;
            poligons[0]->lightIntensity = 0.4;
            // poligons[0]->lightAttenuation = 1;
            poligons[0]->normal[0] = 0;
            poligons[0]->normal[1] = -1;
            poligons[0]->normal[2] = 0;
            poligons[0]->noSize = true;
            // 単位ベクトル化
            l3NormarizeVec3(poligons[0]->normal, poligons[0]->normal);

            l3SetPoligonsToObject(sphere2, sizeof(poligons) / sizeof(l3Poligon*), poligons);
            l3SetTransposeObject(sphere2, 0, 100, 0);
            l3AddObjectToEnvironment(&env, sphere2, "sphere2");
        }

        l3Object* obj3 = l3CreateObject();
        {
            l3AddVertexToObject(obj3, l3CreateVertex(0, 0, 0, &blue));
            l3Mat31A normal = {0, 1, 0};  // 正しい
            l3SetTransposeObject(obj3, 0, -10, 0);
            l3Poligon* poligons[] = {
                l3CreatePoligonPlane(0, normal),
            };
            poligons[0]->material = l3PoligonMaterialColor;
            poligons[0]->color.r = 60;
            poligons[0]->color.g = 60;
            poligons[0]->color.b = 60;
            poligons[0]->metalness[0] = poligons[0]->metalness[1] = poligons[0]->metalness[2] = 0.1;
            poligons[0]->roughness = radians(10);
            poligons[0]->roughnessSamples = 2;

            l3SetPoligonsToObject(obj3, sizeof(poligons) / sizeof(l3Poligon*), poligons);
            l3AddObjectToEnvironment(&env, obj3, "plane");
        }
        l3Object* sky = l3CreateObject();
        {
            l3Poligon* poligons[] = {
                l3CreatePoligonSky(),
            };
            poligons[0]->color.r = 176;
            poligons[0]->color.g = 213;
            poligons[0]->color.b = 255;
            poligons[0]->lightColor = white;
            poligons[0]->lightType = l3LightTypeParallel;
            poligons[0]->lightIntensity = 1;
            poligons[0]->normal[0] = 1;
            poligons[0]->normal[1] = -1;
            poligons[0]->normal[2] = 1;
            l3NormarizeVec3(poligons[0]->normal, poligons[0]->normal);

            l3SetPoligonsToObject(sky, sizeof(poligons) / sizeof(l3Poligon*), poligons);
            l3AddObjectToEnvironment(&env, sky, "sky");
        }

        l3SetCameraInfoToEnvironment(&env, 0, 10, -60,
                                     0, 0, 0,
                                     0, 1, 0,
                                     radians(50), 2, 100000);

        env.environmentColor = white;
        env.environmentLightRate = 0.1;
        env.environmentLightIntensity = 2;
        
        l3MultithreadSequentialRenderer(&env, transition, options);
        l3DestructEnvironment(&env);
    }
    return 0;
}