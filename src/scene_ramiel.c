#include "array.h"
#include "lib3d.h"

static void transition(l3Environment *env, int frame)
{

    int i, mode = 1; //0は普通、１は変形

    l3Object *ramiel_normal = l3FindObject(env, "ramiel_normal");
    l3Vertex *v0 = array_at(&ramiel_normal->vertices, 0);
    l3Vertex *v1 = array_at(&ramiel_normal->vertices, 1);
    l3Vertex *v2 = array_at(&ramiel_normal->vertices, 2);
    l3Vertex *v3 = array_at(&ramiel_normal->vertices, 3);
    l3Vertex *v4 = array_at(&ramiel_normal->vertices, 4);
    l3Vertex *v5 = array_at(&ramiel_normal->vertices, 5);
    l3Vertex *v6 = array_at(&ramiel_normal->vertices, 6);
    l3Vertex *v7 = array_at(&ramiel_normal->vertices, 7);
    l3Vertex *v8 = array_at(&ramiel_normal->vertices, 8);
    l3Vertex *v9 = array_at(&ramiel_normal->vertices, 9);
    l3Vertex *v10 = array_at(&ramiel_normal->vertices, 10);

    l3Object *ramiel_core = l3FindObject(env, "ramiel_core");
    l3Vertex *v11 = array_at(&ramiel_core->vertices, 0);

    l3Object *ramiel_trans = l3FindObject(env, "ramiel_trans");
    l3Vertex *ramielv[36];
    l3Mat41A p[36] = {0};

    l3Object *ramiel_trans2 = l3FindObject(env, "ramiel_trans2");
    l3Vertex *ramielv2[36];
    l3Mat41A p2[36] = {0};

    l3Object *beam = l3FindObject(env, "beam");
    l3Object *ring = l3FindObject(env, "ring");
    l3Object *beamlight = l3FindObject(env, "light6");
    l3Object *beamlight2 = l3FindObject(env, "light7");

    beamlight->dy = 10000;
    beamlight->poligons[0]->lightIntensity = 0;
    beamlight2->dx = 10000;
    beamlight2->dy = 250;
    beamlight2->poligons[0]->sphere_radius = 10;
    beamlight2->poligons[0]->lightIntensity = 1;

    ramiel_normal->theta_y = -2 * PI / 4;
    // ramiel_trans->theta_y = -2*PI / 4;
    ramiel_trans2->sx = 1.5;
    ramiel_trans2->sy = 1.5;
    ramiel_trans2->sz = 1.5;

    l3Vertex *beams[2];
    l3Vertex *rings[2];

    beams[0] = array_at(&beam->vertices, 0);
    beams[1] = array_at(&beam->vertices, 1);
    rings[0] = array_at(&ring->vertices, 0);
    rings[1] = array_at(&ring->vertices, 1);

    for (i = 0; i <= 35; i++)
    {
        ramielv[i] = array_at(&ramiel_trans->vertices, i);
        ramielv2[i] = array_at(&ramiel_trans2->vertices, i);
    }

    if (mode == 0)
    {
        v11->coordinate[1] = v0->coordinate[1];
    }

    if (mode == 1)
    {
        int keyframe1 = 30, keyframe2 = 90, keyframe3 = 120, keyframe4 = 170, keyframe5 = 200, keyframe6 = 260, keyframe7 = 290;

        for (i = 0; i < 36; i++)
        {
            ramielv[i]->coordinate[0] = 0;
            ramielv[i]->coordinate[1] = 0;
            ramielv[i]->coordinate[2] = 0;

            ramielv2[i]->coordinate[0] = 0;
            ramielv2[i]->coordinate[1] = 0;
            ramielv2[i]->coordinate[2] = 0;
        }
        rings[0]->coordinate[0] = 0;
        rings[0]->coordinate[1] = ramiel_core->dy;
        rings[0]->coordinate[2] = 0;

        rings[1]->coordinate[0] = 0;
        rings[1]->coordinate[1] = ramiel_core->dy;
        rings[1]->coordinate[2] = 0;

        ring->poligons[0]->boundingRadius = 800;

        beams[0]->coordinate[0] = 0;
        beams[0]->coordinate[1] = ramiel_core->dy;
        beams[0]->coordinate[2] = 0;

        beams[1]->coordinate[0] = 0;
        beams[1]->coordinate[1] = ramiel_core->dy;
        beams[1]->coordinate[2] = 0;

        if (frame < keyframe1)
        {

            ramiel_normal->dy = 800 - 600 * l3TimeTransition(l3TimeType_linear, frame, 0, keyframe1);
        }

        if (frame >= keyframe1 && frame < keyframe2)
        {

            bezier in[2], l1[2], l2[2], l3[2], l4[2];
            {
                l3SetBezierPoint(&in[0], 0, 0, 200);
                l3SetBezierPoint(&in[1], 0, 0, 0);

                l3SetBezierPoint(&l1[0], 0, 0, 200);
                l3SetBezierPoint(&l1[1], 200, 0, 0);
                l3SetBezierPoint(&l2[0], 0, 0, 200);
                l3SetBezierPoint(&l2[1], -200, 0, 0);
                l3SetBezierPoint(&l3[0], 0, 0, 200);
                l3SetBezierPoint(&l3[1], 0, 200, 0);
                l3SetBezierPoint(&l4[0], 0, 0, 200);
                l3SetBezierPoint(&l4[1], 0, -200, 0);
            }

            l3BezierToMat41A(v4->coordinate, l3GetBezierCurve(l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe1, keyframe2), 2, in));
            l3BezierToMat41A(v7->coordinate, l3GetBezierCurve(l3TimeTransition(l3TimeType_linear, frame, keyframe1, keyframe2), 2, l3));
            l3BezierToMat41A(v8->coordinate, l3GetBezierCurve(l3TimeTransition(l3TimeType_linear, frame, keyframe1, keyframe2), 2, l1));
            l3BezierToMat41A(v9->coordinate, l3GetBezierCurve(l3TimeTransition(l3TimeType_linear, frame, keyframe1, keyframe2), 2, l4));
            l3BezierToMat41A(v10->coordinate, l3GetBezierCurve(l3TimeTransition(l3TimeType_linear, frame, keyframe1, keyframe2), 2, l2));

            // l3PrintMat(v4->coordinate, 4, 1);
            // l3PrintMat(v7->coordinate, 4, 1);
            // l3PrintMat(v8->coordinate, 4, 1);
            // l3PrintMat(v9->coordinate, 4, 1);
            // l3PrintMat(v10->coordinate, 4, 1);
        }

        if (frame >= keyframe2 && frame <= keyframe3)
        {
            bezier in[2], l1[2], l2[2], l3[2], l4[2], l5[2];
            {
                l3SetBezierPoint(&in[0], 0, 0, 0);
                l3SetBezierPoint(&in[1], 0, 0, 0);

                l3SetBezierPoint(&l1[1], 0, 0, 0);
                l3SetBezierPoint(&l1[0], 200, 0, 0);
                l3SetBezierPoint(&l2[1], 0, 0, 0);
                l3SetBezierPoint(&l2[0], -200, 0, 0);
                l3SetBezierPoint(&l3[1], 0, 0, 0);
                l3SetBezierPoint(&l3[0], 0, 200, 0);
                l3SetBezierPoint(&l4[1], 0, 0, 0);
                l3SetBezierPoint(&l4[0], 0, -200, 0);
                l3SetBezierPoint(&l5[1], 0, 0, 0);
                l3SetBezierPoint(&l5[0], 0, 0, -200);
            }

            l3BezierToMat41A(v3->coordinate, l3GetBezierCurve(l3TimeTransition(l3TimeType_linear, frame, keyframe2, keyframe3), 2, l5));
            l3BezierToMat41A(v4->coordinate, l3GetBezierCurve(l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe2, keyframe3), 2, in));
            l3BezierToMat41A(v7->coordinate, l3GetBezierCurve(l3TimeTransition(l3TimeType_linear, frame, keyframe2, keyframe3), 2, l3));
            l3BezierToMat41A(v8->coordinate, l3GetBezierCurve(l3TimeTransition(l3TimeType_linear, frame, keyframe2, keyframe3), 2, l1));
            l3BezierToMat41A(v9->coordinate, l3GetBezierCurve(l3TimeTransition(l3TimeType_linear, frame, keyframe2, keyframe3), 2, l4));
            l3BezierToMat41A(v10->coordinate, l3GetBezierCurve(l3TimeTransition(l3TimeType_linear, frame, keyframe2, keyframe3), 2, l2));
            l3BezierToMat41A(v1->coordinate, l3GetBezierCurve(l3TimeTransition(l3TimeType_linear, frame, keyframe2, keyframe3), 2, l3));
            l3BezierToMat41A(v2->coordinate, l3GetBezierCurve(l3TimeTransition(l3TimeType_linear, frame, keyframe2, keyframe3), 2, l1));
            l3BezierToMat41A(v6->coordinate, l3GetBezierCurve(l3TimeTransition(l3TimeType_linear, frame, keyframe2, keyframe3), 2, l4));
            l3BezierToMat41A(v5->coordinate, l3GetBezierCurve(l3TimeTransition(l3TimeType_linear, frame, keyframe2, keyframe3), 2, l2));

            // l3PrintMat(v4->coordinate, 4, 1);
            // l3PrintMat(v7->coordinate, 4, 1);
            // l3PrintMat(v8->coordinate, 4, 1);
            // l3PrintMat(v9->coordinate, 4, 1);
            // l3PrintMat(v10->coordinate, 4, 1);
        }

        if (frame >= keyframe2)
        {

            for (i = 1; i <= 5; i++)
            {
                l3PolarToMat41A(p[1 + 7 * (i - 1)], 30 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe2, keyframe3), PI, PI / 2 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p[2 + 7 * (i - 1)], 100 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe2, keyframe3), 5 * PI / 6 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe2, keyframe3) + PI / 6 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe4, keyframe6), PI / 2 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p[3 + 7 * (i - 1)], 300 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe2, keyframe3), (PI / 2 - PI / 6) * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe2, keyframe3) + PI / 6 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe4, keyframe6), PI / 2 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p[4 + 7 * (i - 1)], 100 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe2, keyframe3), (PI / 2 - PI / 12) * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe2, keyframe3) + PI / 6 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe4, keyframe6), PI / 2 - PI / 10 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p[5 + 7 * (i - 1)], 80 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe2, keyframe3), (PI / 2 - PI / 20) * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe2, keyframe3) + PI / 6 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe4, keyframe6), PI / 2 - PI / 10 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p[6 + 7 * (i - 1)], 30 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe2, keyframe3), (PI / 4) * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe2, keyframe3) + PI / 6 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe4, keyframe6), PI / 2 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p[7 + 7 * (i - 1)], 30 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe2, keyframe3), (PI / 3) * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe2, keyframe3) + PI / 6 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe4, keyframe6), PI / 2 - PI / 10 + 2 * PI / 5 * (i - 1));
            }

            for (i = 0; i < 36; i++)
            {
                ramielv[i]->coordinate[0] = p[i][0];
                ramielv[i]->coordinate[1] = p[i][1];
                ramielv[i]->coordinate[2] = p[i][2];
            }

            ramiel_trans->theta_x += (2 * PI / 30) * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe2, keyframe3) * (1.1 - l3TimeTransition(l3TimeType_linear, frame, keyframe4, keyframe5)) * (1 - l3TimeTransition(l3TimeType_linear, frame, keyframe5, keyframe6));
        }

        if (frame >= keyframe3)
        {
            for (i = 1; i <= 5; i++)
            {
                l3PolarToMat41A(p2[1 + 7 * (i - 1)], 30 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe3, keyframe4), PI, PI / 2 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p2[2 + 7 * (i - 1)], 100 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe3, keyframe4), 5 * PI / 6 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe3, keyframe4) + PI / 6 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe4, keyframe6), PI / 2 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p2[3 + 7 * (i - 1)], 300 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe3, keyframe4), (PI / 2 - PI / 6) * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe3, keyframe4) + PI / 6 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe4, keyframe6), PI / 2 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p2[4 + 7 * (i - 1)], 100 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe3, keyframe4), (PI / 2 - PI / 12) * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe3, keyframe4) + PI / 6 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe4, keyframe6), PI / 2 - PI / 10 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p2[5 + 7 * (i - 1)], 80 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe3, keyframe4), (PI / 2 - PI / 20) * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe3, keyframe4) + PI / 6 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe4, keyframe6), PI / 2 - PI / 10 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p2[6 + 7 * (i - 1)], 30 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe3, keyframe4), (PI / 4) * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe3, keyframe4) + PI / 6 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe4, keyframe6), PI / 2 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p2[7 + 7 * (i - 1)], 30 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe3, keyframe4), (PI / 3) * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe3, keyframe4) + PI / 6 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe4, keyframe6), PI / 2 - PI / 10 + 2 * PI / 5 * (i - 1));
            }

            for (i = 0; i < 36; i++)
            {
                ramielv2[i]->coordinate[0] = p2[i][0];
                ramielv2[i]->coordinate[1] = p2[i][1];
                ramielv2[i]->coordinate[2] = p2[i][2];
            }

            ramiel_trans2->theta_x -= (2 * PI / 30) * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe3, keyframe4) * (1.1 - l3TimeTransition(l3TimeType_linear, frame, keyframe4, keyframe5)) * (1 - l3TimeTransition(l3TimeType_linear, frame, keyframe5, keyframe6));
        }

        if (frame >= keyframe5)
        {

            beamlight2->dx = 1000 - 700 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe5, keyframe6);
            beamlight2->dy = 250;
            beamlight2->poligons[0]->sphere_radius = 200 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe5, keyframe6);
            beamlight2->poligons[0]->lightIntensity = 100 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe5, keyframe6);

            ring->poligons[0]->lightIntensity = 1000 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe5, keyframe6);

            rings[0]->coordinate[0] = 70;
            rings[0]->coordinate[1] = ramiel_core->dy;
            rings[0]->coordinate[2] = 0;

            rings[1]->coordinate[0] = 90;
            rings[1]->coordinate[1] = ramiel_core->dy;
            rings[1]->coordinate[2] = 0;

            ring->poligons[0]->sphere_radius = 500 * (1.0 - l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe5, keyframe6));

            beams[0]->coordinate[0] = 0;
            beams[0]->coordinate[1] = ramiel_core->dy;
            beams[0]->coordinate[2] = 0;

            ramiel_core->poligons[0]->lightIntensity = 100 * l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe5, keyframe6);

            if (frame >= keyframe6)
            {
                ring->poligons[0]->lightIntensity = 100 * (1.0 - l3TimeTransition(l3TimeType_EasyEaseOut, frame, keyframe6, keyframe7));
                beam->poligons[0]->lightIntensity = 1000 * rand();
                beams[1]->coordinate[0] = 1000;
                beams[1]->coordinate[1] = ramiel_core->dy;
                beams[1]->coordinate[2] = 0;
                beamlight->poligons[0]->lightIntensity = 1000 * rand();
            }
        }
        // if(mode == 2){
        //     l3PolarToMat41A(v1->coordinate,300,);
        // }

        ramiel_core->dy = ramiel_normal->dy = ramiel_trans->dy = ramiel_trans2->dy;
        ramiel_trans2->dx = ramiel_trans->dx - 50;

        l3Object *light1 = l3FindObject(env, "light1");
        light1->dx = 800 * cos(-67 / 100.0 * 2.0 * PI);
        light1->dz = 800 * sin(-67 / 100.0 * 2.0 * PI);

        bezier cpoint[8];
        {
            cpoint[0].x = 800 * cos(-67 / 100.0 * 2.0 * PI);
            cpoint[0].y = 5;
            cpoint[0].z = 800 * sin(-67 / 100.0 * 2.0 * PI);
            cpoint[1].x = 550;
            cpoint[1].y = 100;
            cpoint[1].z = 300;
            cpoint[2].x = 0;
            cpoint[2].y = 10;
            cpoint[2].z = -100;
            cpoint[3].x = -70;
            cpoint[3].y = 20;
            cpoint[3].z = 40;
            cpoint[4].x = 0;
            cpoint[4].y = 5;
            cpoint[4].z = -70;
            cpoint[5].x = -100;
            cpoint[5].y = 40;
            cpoint[5].z = 70;
            cpoint[6].x = -80;
            cpoint[6].y = 100;
            cpoint[6].z = -30;
            cpoint[7].x = 500;
            cpoint[7].y = 300;
            cpoint[7].z = -500;
        }

        bezier camera_bezier = l3GetBezierCurve(l3TimeTransition(l3TimeType_EasyEase, frame, 0, keyframe6), 8, cpoint);

        // env->camera.coordinate[0] = camera_bezier.x;
        // env->camera.coordinate[1] = camera_bezier.y;
        // env->camera.coordinate[2] = camera_bezier.z;
        // env->camera.target[0] = 0;
        // env->camera.target[1] = 250;
        // env->camera.target[2] = 0;

        if (frame >= keyframe6)
        {

            env->camera.coordinate[0] = 500 + 20 * sin((frame-keyframe6)/5.0*2.0*PI);
            env->camera.coordinate[1] = 300 + 20 * sin((frame-keyframe6)/3.0*2.0*PI);
            env->camera.coordinate[2] = -500 + 20 * sin((frame-keyframe6)/4.0*2.0*PI);
            env->camera.target[0] = 0 + 20 * sin((frame-keyframe6)/6.0*2.0*PI);
            env->camera.target[1] = 250 + 20 * sin((frame-keyframe6)/2.0*2.0*PI);
            env->camera.target[2] = 0 + 20 * sin((frame-keyframe6)/3.0*2.0*PI);
        }
        else
        {
            env->camera.coordinate[0] = camera_bezier.x;
            env->camera.coordinate[1] = camera_bezier.y;
            env->camera.coordinate[2] = camera_bezier.z;
            env->camera.target[0] = 0;
            env->camera.target[1] = 250;
            env->camera.target[2] = 0;
        }
    }
}

int scene_ramiel(int argc, const char *argv[], l3Options *options)
{
    l3Environment env;
    {
        int i;
        l3RGB red = {255, 0, 0};
        l3RGB green = {0, 255, 0};
        l3RGB blue = {0, 0, 255};
        l3RGB white = {255, 255, 255};
        l3RGB ramiel_blue = {100, 100, 250};
        l3RGB ramiel_pink = {220, 100, 100};
        l3InitializeEnvironment(&env);
        env.w = options->w;
        env.h = options->h;
        env.outdir = options->outdir;

        // オブジェクト構築

        l3Object *ramiel_normal = l3CreateObject();
        {
            int vs[] = {
                l3AddVertexToObject(ramiel_normal, l3CreateVertex(0, 0, 0, &ramiel_blue)), //0
                l3AddVertexToObject(ramiel_normal, l3CreateVertex(0, 200, 0, &ramiel_blue)),
                l3AddVertexToObject(ramiel_normal, l3CreateVertex(200, 0, 0, &ramiel_blue)),
                l3AddVertexToObject(ramiel_normal, l3CreateVertex(0, 0, -200, &ramiel_blue)),
                l3AddVertexToObject(ramiel_normal, l3CreateVertex(0, 0, 200, &ramiel_blue)),
                l3AddVertexToObject(ramiel_normal, l3CreateVertex(-200, 0, 0, &ramiel_blue)),
                l3AddVertexToObject(ramiel_normal, l3CreateVertex(0, -200, 0, &ramiel_blue)), //6

                l3AddVertexToObject(ramiel_normal, l3CreateVertex(0, 0, 200, &ramiel_blue)), //7 開くよう
                l3AddVertexToObject(ramiel_normal, l3CreateVertex(0, 0, 200, &ramiel_blue)),
                l3AddVertexToObject(ramiel_normal, l3CreateVertex(0, 0, 200, &ramiel_blue)),
                l3AddVertexToObject(ramiel_normal, l3CreateVertex(0, 0, 200, &ramiel_blue)),
            };

            // 右回りが表、数字はオブジェクトごとの頂点のインデックス
            l3Poligon *poligons[] = {
                l3CreatePoligon(1, 3, 2),
                l3CreatePoligon(1, 5, 3),
                l3CreatePoligon(6, 2, 3),
                l3CreatePoligon(6, 3, 5),

                l3CreatePoligon(4, 7, 8),
                l3CreatePoligon(4, 8, 9),
                l3CreatePoligon(4, 9, 10),
                l3CreatePoligon(4, 10, 7),

                l3CreatePoligon(5, 1, 10),
                l3CreatePoligon(1, 7, 10),
                l3CreatePoligon(1, 2, 7),
                l3CreatePoligon(2, 8, 7),
                l3CreatePoligon(2, 6, 8),
                l3CreatePoligon(6, 9, 8),
                l3CreatePoligon(5, 9, 6),
                l3CreatePoligon(5, 10, 9),

            };

            for (i = 0; i < 16; i++)
            {
                poligons[i]->material = l3PoligonMaterialColor;
                poligons[i]->color = ramiel_blue;

                poligons[i]->metalness[0] = 0.5;
                poligons[i]->metalness[1] = 0.5;
                poligons[i]->metalness[2] = 0.00009;
                poligons[i]->transparency = 0.0001;
            }

            // poligons[0]->lightType        = poligons[1]->lightType        = poligons[2]->lightType        = poligons[3]->lightType        = poligons[4]->lightType        = poligons[5]->lightType        = poligons[6]->lightType        = poligons[7]->lightType        = l3LightTypeParallel;
            // poligons[0]->lightIntensity   = poligons[1]->lightIntensity   = poligons[2]->lightIntensity   = poligons[3]->lightIntensity   = poligons[4]->lightIntensity   = poligons[5]->lightIntensity   = poligons[6]->lightIntensity   = poligons[7]->lightIntensity   = 0.01;
            // poligons[0]->lightAttenuation = poligons[1]->lightAttenuation = poligons[2]->lightAttenuation = poligons[3]->lightAttenuation = poligons[4]->lightAttenuation = poligons[5]->lightAttenuation = poligons[6]->lightAttenuation = poligons[7]->lightAttenuation = 0.4;

            // テクスチャ読み込み・貼り付け
            // l3Texture texture;
            // l3Load2DTexture("assets/tex4.ppm", &texture);
            // l3Mat32A texture_vertices = {0.5, 0.5, 0, 1, 1, 1};
            l3SetPoligonsToObject(ramiel_normal, sizeof(poligons) / sizeof(l3Poligon *), poligons);
            l3SetTransposeObject(ramiel_normal, 0, 250, 0);
            l3SetScaleObject(ramiel_normal, 1, 1, 1);
            l3AddObjectToEnvironment(&env, ramiel_normal, "ramiel_normal");
        }

        l3Object *ramiel_trans = l3CreateObject();
        {

            l3Mat41A p[36] = {0};
            l3PolarToMat41A(p[0], 0, 0, 0);

            for (i = 1; i <= 5; i++)
            {
                l3PolarToMat41A(p[1 + 7 * (i - 1)], 30, PI, PI / 2 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p[2 + 7 * (i - 1)], 100, 5 * PI / 6, PI / 2 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p[3 + 7 * (i - 1)], 300, PI / 2 - PI / 6, PI / 2 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p[4 + 7 * (i - 1)], 100, PI / 2 - PI / 12, PI / 2 - PI / 10 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p[5 + 7 * (i - 1)], 80, PI / 2 - PI / 20, PI / 2 - PI / 10 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p[6 + 7 * (i - 1)], 30, PI / 6, PI / 2 + 2 * PI / 5 * (i - 1));
                l3PolarToMat41A(p[7 + 7 * (i - 1)], 30, PI / 4, PI / 2 - PI / 10 + 2 * PI / 5 * (i - 1));
            }

            int vs[] = {

                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[0][0], p[0][1], p[0][2], &ramiel_blue)), //0
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[1][0], p[1][1], p[1][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[2][0], p[2][1], p[2][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[3][0], p[3][1], p[3][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[4][0], p[4][1], p[4][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[5][0], p[5][1], p[5][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[6][0], p[6][1], p[6][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[7][0], p[7][1], p[7][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[8][0], p[8][1], p[8][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[9][0], p[9][1], p[9][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[10][0], p[10][1], p[10][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[11][0], p[11][1], p[11][2], &ramiel_blue)), //0
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[12][0], p[12][1], p[12][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[13][0], p[13][1], p[13][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[14][0], p[14][1], p[14][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[15][0], p[15][1], p[15][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[16][0], p[16][1], p[16][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[17][0], p[17][1], p[17][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[18][0], p[18][1], p[18][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[19][0], p[19][1], p[19][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[20][0], p[20][1], p[20][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[21][0], p[21][1], p[21][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[22][0], p[22][1], p[22][2], &ramiel_blue)), //0
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[23][0], p[23][1], p[23][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[24][0], p[24][1], p[24][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[25][0], p[25][1], p[25][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[26][0], p[26][1], p[26][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[27][0], p[27][1], p[27][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[28][0], p[28][1], p[28][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[29][0], p[29][1], p[29][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[30][0], p[30][1], p[30][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[31][0], p[31][1], p[31][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[32][0], p[32][1], p[32][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[33][0], p[33][1], p[33][2], &ramiel_blue)), //0
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[34][0], p[34][1], p[34][2], &ramiel_blue)),
                l3AddVertexToObject(ramiel_trans, l3CreateVertex(p[35][0], p[35][1], p[35][2], &ramiel_blue)),
            };

            // 右回りが表、数字はオブジェクトごとの頂点のインデックス

            l3Poligon *poligons[] = {

                l3CreatePoligon(3 + 7 * 0, 4 + 7 * 0, 6 + 7 * 0), //0
                l3CreatePoligon(6 + 7 * 0, 4 + 7 * 0, 7 + 7 * 0),
                l3CreatePoligon(0 + 7 * 0, 6 + 7 * 0, 7 + 7 * 0),
                l3CreatePoligon(7 + 7 * 0, 4 + 7 * 0, 6 + 7 * (0 + 1)),
                l3CreatePoligon(0 + 7 * 0, 7 + 7 * 0, 6 + 7 * (0 + 1)),
                l3CreatePoligon(4 + 7 * 0, 3 + 7 * (0 + 1), 6 + 7 * (0 + 1)),
                l3CreatePoligon(2 + 7 * 0, 4 + 7 * 0, 3 + 7 * 0),
                l3CreatePoligon(2 + 7 * 0, 5 + 7 * 0, 4 + 7 * 0),
                l3CreatePoligon(4 + 7 * 0, 5 + 7 * 0, 2 + 7 * (0 + 1)),
                l3CreatePoligon(3 + 7 * (0 + 1), 4 + 7 * 0, 2 + 7 * (0 + 1)), //9

                l3CreatePoligon(3 + 7 * 1, 4 + 7 * 1, 6 + 7 * 1), //0
                l3CreatePoligon(6 + 7 * 1, 4 + 7 * 1, 7 + 7 * 1),
                l3CreatePoligon(0 + 7 * 1, 6 + 7 * 1, 7 + 7 * 1),
                l3CreatePoligon(7 + 7 * 1, 4 + 7 * 1, 6 + 7 * (1 + 1)),
                l3CreatePoligon(0 + 7 * 1, 7 + 7 * 1, 6 + 7 * (1 + 1)),
                l3CreatePoligon(4 + 7 * 1, 3 + 7 * (1 + 1), 6 + 7 * (1 + 1)),
                l3CreatePoligon(2 + 7 * 1, 4 + 7 * 1, 3 + 7 * 1),
                l3CreatePoligon(2 + 7 * 1, 5 + 7 * 1, 4 + 7 * 1),
                l3CreatePoligon(4 + 7 * 1, 5 + 7 * 1, 2 + 7 * (1 + 1)),
                l3CreatePoligon(3 + 7 * (1 + 1), 4 + 7 * 1, 2 + 7 * (1 + 1)), //9

                l3CreatePoligon(3 + 7 * 2, 4 + 7 * 2, 6 + 7 * 2), //0
                l3CreatePoligon(6 + 7 * 2, 4 + 7 * 2, 7 + 7 * 2),
                l3CreatePoligon(0 + 7 * 2, 6 + 7 * 2, 7 + 7 * 2),
                l3CreatePoligon(7 + 7 * 2, 4 + 7 * 2, 6 + 7 * (2 + 1)),
                l3CreatePoligon(0 + 7 * 2, 7 + 7 * 2, 6 + 7 * (2 + 1)),
                l3CreatePoligon(4 + 7 * 2, 3 + 7 * (2 + 1), 6 + 7 * (2 + 1)),
                l3CreatePoligon(2 + 7 * 2, 4 + 7 * 2, 3 + 7 * 2),
                l3CreatePoligon(2 + 7 * 2, 5 + 7 * 2, 4 + 7 * 2),
                l3CreatePoligon(4 + 7 * 2, 5 + 7 * 2, 2 + 7 * (2 + 1)),
                l3CreatePoligon(3 + 7 * (2 + 1), 4 + 7 * 2, 2 + 7 * (2 + 1)), //9

                l3CreatePoligon(3 + 7 * 3, 4 + 7 * 3, 6 + 7 * 3), //0
                l3CreatePoligon(6 + 7 * 3, 4 + 7 * 3, 7 + 7 * 3),
                l3CreatePoligon(0 + 7 * 3, 6 + 7 * 3, 7 + 7 * 3),
                l3CreatePoligon(7 + 7 * 3, 4 + 7 * 3, 6 + 7 * (3 + 1)),
                l3CreatePoligon(0 + 7 * 3, 7 + 7 * 3, 6 + 7 * (3 + 1)),
                l3CreatePoligon(4 + 7 * 3, 3 + 7 * (3 + 1), 6 + 7 * (3 + 1)),
                l3CreatePoligon(2 + 7 * 3, 4 + 7 * 3, 3 + 7 * 3),
                l3CreatePoligon(2 + 7 * 3, 5 + 7 * 3, 4 + 7 * 3),
                l3CreatePoligon(4 + 7 * 3, 5 + 7 * 3, 2 + 7 * (3 + 1)),
                l3CreatePoligon(3 + 7 * (3 + 1), 4 + 7 * 3, 2 + 7 * (3 + 1)), //9

                l3CreatePoligon(3 + 7 * 4, 4 + 7 * 4, 6 + 7 * 4), //0
                l3CreatePoligon(6 + 7 * 4, 4 + 7 * 4, 7 + 7 * 4),
                l3CreatePoligon(0 + 7 * 4, 6 + 7 * 4, 7 + 7 * 4),
                l3CreatePoligon(7 + 7 * 4, 4 + 7 * 4, 6 + 7 * 0),
                l3CreatePoligon(0 + 7 * 4, 7 + 7 * 4, 6 + 7 * 0),
                l3CreatePoligon(4 + 7 * 4, 3 + 7 * 0, 6 + 7 * 0),
                l3CreatePoligon(2 + 7 * 4, 4 + 7 * 4, 3 + 7 * 4),
                l3CreatePoligon(2 + 7 * 4, 5 + 7 * 4, 4 + 7 * 4),
                l3CreatePoligon(4 + 7 * 4, 5 + 7 * 4, 2 + 7 * 0),
                l3CreatePoligon(3 + 7 * 0, 4 + 7 * 4, 2 + 7 * 0), //9

            };

            for (i = 0; i <= 4; i++)
            {
                poligons[i * 10]->material = l3PoligonMaterialColor;
                poligons[i * 10]->color = ramiel_blue;

                poligons[1 + i * 10]->material = l3PoligonMaterialColor;
                poligons[1 + i * 10]->color = ramiel_pink;

                poligons[2 + i * 10]->material = l3PoligonMaterialColor;
                poligons[2 + i * 10]->color = ramiel_pink;

                poligons[3 + i * 10]->material = l3PoligonMaterialColor;
                poligons[3 + i * 10]->color = ramiel_pink;

                poligons[4 + i * 10]->material = l3PoligonMaterialColor;
                poligons[4 + i * 10]->color = ramiel_pink;

                poligons[5 + i * 10]->material = l3PoligonMaterialColor;
                poligons[5 + i * 10]->color = ramiel_blue;

                poligons[6 + i * 10]->material = l3PoligonMaterialColor;
                poligons[6 + i * 10]->color = ramiel_blue;

                poligons[7 + i * 10]->material = l3PoligonMaterialColor;
                poligons[7 + i * 10]->color = ramiel_blue;

                poligons[8 + i * 10]->material = l3PoligonMaterialColor;
                poligons[8 + i * 10]->color = ramiel_blue;

                poligons[9 + i * 10]->material = l3PoligonMaterialColor;
                poligons[9 + i * 10]->color = ramiel_blue;
            }

            for (i = 0; i <= 36; i++)
            {
                poligons[i]->metalness[0] = 0.5;
                poligons[i]->metalness[1] = 0.5;
                poligons[i]->metalness[2] = 0.0005;
                poligons[i]->transparency = 0.05;
            }

            // poligons[0]->lightType        = poligons[1]->lightType        = poligons[2]->lightType        = poligons[3]->lightType        = poligons[4]->lightType        = poligons[5]->lightType        = poligons[6]->lightType        = poligons[7]->lightType        = l3LightTypeParallel;
            // poligons[0]->lightIntensity   = poligons[1]->lightIntensity   = poligons[2]->lightIntensity   = poligons[3]->lightIntensity   = poligons[4]->lightIntensity   = poligons[5]->lightIntensity   = poligons[6]->lightIntensity   = poligons[7]->lightIntensity   = 0.01;
            // poligons[0]->lightAttenuation = poligons[1]->lightAttenuation = poligons[2]->lightAttenuation = poligons[3]->lightAttenuation = poligons[4]->lightAttenuation = poligons[5]->lightAttenuation = poligons[6]->lightAttenuation = poligons[7]->lightAttenuation = 0.4;

            // テクスチャ読み込み・貼り付け
            // l3Texture texture;
            // l3Load2DTexture("assets/tex4.ppm", &texture);
            // l3Mat32A texture_vertices = {0.5, 0.5, 0, 1, 1, 1};
            l3SetPoligonsToObject(ramiel_trans, sizeof(poligons) / sizeof(l3Poligon *), poligons);
            l3SetTransposeObject(ramiel_trans, 0, 250, 0);
            l3SetScaleObject(ramiel_trans, 1, 1, 1);
            l3AddObjectToEnvironment(&env, ramiel_trans, "ramiel_trans");
        }

        l3Object *ramiel_trans2 = l3CloneObject(ramiel_trans);
        {
            l3AddObjectToEnvironment(&env, ramiel_trans2, "ramiel_trans2");
        }

        l3Object *light1 = l3CreateObject();
        {
            int vs[] = {
                l3AddVertexToObject(light1, l3CreateVertex(0, 0, 0, &red)),
                l3AddVertexToObject(light1, l3CreateVertex(0, 100, 0, &red)),
            };
            l3Poligon *poligons[] = {
                l3CreatePoligonSphere(0, 1, 100),
            };
            poligons[0]->lightColor.r = 20;
            poligons[0]->lightColor.g = 20;
            poligons[0]->lightColor.b = 250;
            poligons[0]->material = l3PoligonMaterialColor;
            poligons[0]->lightType = l3LightTypePoint;
            poligons[0]->lightIntensity = 1000;
            poligons[0]->transparency = 1;
            poligons[0]->lightAttenuation = 0.0004;

            l3SetPoligonsToObject(light1, sizeof(poligons) / sizeof(l3Poligon *), poligons);
            l3SetTransposeObject(light1, -3000, 200, -3000);
            l3AddObjectToEnvironment(&env, light1, "light1");
        }

        l3Object *light2 = l3CloneObject(light1);
        {
            light2->poligons[0]->lightColor.r = 200;
            light2->poligons[0]->lightColor.g = 20;
            light2->poligons[0]->lightColor.b = 120;
            light2->poligons[0]->transparency = 1;

            light2->poligons[0]->lightIntensity = 1000;

            l3SetTransposeObject(light2, 800, 400, 300);
            l3AddObjectToEnvironment(&env, light2, "light2");
        }

        l3Object *light3 = l3CloneObject(light1);
        {
            light3->poligons[0]->lightColor.r = 40;
            light3->poligons[0]->lightColor.g = 40;
            light3->poligons[0]->lightColor.b = 255;
            light3->poligons[0]->transparency = 1;

            light3->poligons[0]->lightIntensity = 100;

            l3SetTransposeObject(light3, 50, 1200, 100);
            l3AddObjectToEnvironment(&env, light3, "light3");
        }

        l3Object *light4 = l3CloneObject(light1);
        {
            light4->poligons[0]->lightColor.r = 220;
            light4->poligons[0]->lightColor.g = 40;
            light4->poligons[0]->lightColor.b = 140;
            light4->poligons[0]->transparency = 1;

            light4->poligons[0]->lightIntensity = 100;

            l3SetTransposeObject(light3, 50, 0, -100);
            l3AddObjectToEnvironment(&env, light4, "light4");
        }

        l3Object *light5 = l3CloneObject(light1);
        {
            light5->poligons[0]->lightColor.r = 220;
            light5->poligons[0]->lightColor.g = 40;
            light5->poligons[0]->lightColor.b = 140;
            light5->poligons[0]->transparency = 1;
            light5->poligons[0]->lightIntensity = 100;

            l3SetTransposeObject(light5, -150, 200, -500);
            l3AddObjectToEnvironment(&env, light5, "light5");
        }

        l3Object *light6 = l3CloneObject(light1);
        {
            light6->poligons[0]->lightColor.r = 250;
            light6->poligons[0]->lightColor.g = 220;
            light6->poligons[0]->lightColor.b = 100;
            light6->poligons[0]->transparency = 1;
            light6->poligons[0]->lightIntensity = 100;

            l3SetTransposeObject(light6, 100, 250, 0);
            l3AddObjectToEnvironment(&env, light6, "light6");
        }

        l3Object *light7 = l3CloneObject(light1);
        {
            light7->poligons[0]->lightColor.r = 250;
            light7->poligons[0]->lightColor.g = 20;
            light7->poligons[0]->lightColor.b = 10;
            light7->poligons[0]->transparency = 1;
            light7->poligons[0]->lightIntensity = 100;

            l3SetTransposeObject(light7, 100, 250, 0);
            l3AddObjectToEnvironment(&env, light7, "light7");
        }

        l3Object *ramiel_core = l3CreateObject();
        {
            int vs[] = {

                l3AddVertexToObject(ramiel_core, l3CreateVertex(0, 0, 0, &red)),
                l3AddVertexToObject(ramiel_core, l3CreateVertex(0, 5, 0, &red)),
            };
            l3Poligon *poligons[] = {
                l3CreatePoligonSphere(0, 1, 20),
            };

            poligons[0]->color.r = 200;
            poligons[0]->lightColor.r = 255;
            poligons[0]->lightColor.g = 0;
            poligons[0]->lightColor.b = 35;
            poligons[0]->lightType = l3LightTypePoint;
            poligons[0]->lightIntensity = 2;
            poligons[0]->lightAttenuation = 0.4;

            l3SetPoligonsToObject(ramiel_core, sizeof(poligons) / sizeof(l3Poligon *), poligons);
            l3SetTransposeObject(ramiel_core, 0, 250, 0);
            l3SetScaleObject(ramiel_core, 10, 10, 10);
            l3AddObjectToEnvironment(&env, ramiel_core, "ramiel_core");
        }

        l3Object *ring = l3CreateObject();
        {
            int vs[] = {
                l3AddVertexToObject(ring, l3CreateVertex(0, 0, 0, &red)),
                l3AddVertexToObject(ring, l3CreateVertex(0, 20, 0, &red)),
            };
            l3Poligon *poligons[] = {
                l3CreatePoligonColumn(0, 1, 10),
            };
            poligons[0]->color.r = 255;
            poligons[0]->color.g = 250;
            poligons[0]->color.b = 50;
            light5->poligons[0]->transparency = 0.7;
            poligons[0]->material = l3PoligonMaterialColor;
            poligons[0]->lightIntensity = 1000;
            poligons[0]->lightType = l3LightTypePoint;
            poligons[0]->lightAttenuation = 0.004;

            l3SetPoligonsToObject(ring, sizeof(poligons) / sizeof(l3Poligon *), poligons);
            l3SetTransposeObject(ring, 0, 0, 0);
            //l3SetScaleObject(ring, 10, 1, 10);
            l3AddObjectToEnvironment(&env, ring, "ring");
        }

        l3Object *beam = l3CreateObject();
        {
            int vs[] = {
                l3AddVertexToObject(beam, l3CreateVertex(0, 0, 0, &red)),
                l3AddVertexToObject(beam, l3CreateVertex(0, 20, 0, &red)),
            };
            l3Poligon *poligons[] = {
                l3CreatePoligonColumn(0, 1, 10),
            };
            poligons[0]->color.r = 55;
            poligons[0]->color.g = 50;
            poligons[0]->color.b = 250;
            light5->poligons[0]->transparency = 0.7;
            poligons[0]->material = l3PoligonMaterialColor;
            poligons[0]->lightIntensity = 1000;
            poligons[0]->lightType = l3LightTypePoint;
            poligons[0]->lightAttenuation = 0.004;

            l3SetPoligonsToObject(beam, sizeof(poligons) / sizeof(l3Poligon *), poligons);
            l3SetTransposeObject(beam, 0, 0, 0);
            //l3SetScaleObject(ring, 10, 1000, 10);
            l3AddObjectToEnvironment(&env, beam, "beam");
        }

        l3Object *b01 = l3CreateBox();
        {
            // テクスチャ読み込み
            //l3Texture texture;
            //l3Load2DTexture("assets/building.ppm", &texture);
            int i;
            for (i = 0; i < 11; ++i)
            {
                b01->poligons[i]->color.r = 0;
                b01->poligons[i]->color.g = 0;
                b01->poligons[i]->color.b = 0;
            }
            //テクスチャ読み込み・貼り付け
            for (i = 0; i < 11; ++i)
            {
                l3Texture texture;
                l3Load2DTexture("assets/building.ppm", &texture);
                l3Mat32A texture_vertices = {0.5, 0.5, 0, 1, 1, 1};
                b01->poligons[i]->textureType = l3TextureTypeTiled;
                b01->poligons[i]->textureRepeatX = 0.5;
                b01->poligons[i]->textureRepeatY = 0.5;
                b01->poligons[i]->textureCoordinateSystem = l3CoordinateSystemLocal;
                b01->poligons[i]->texture = &texture;
            }

            //obj01->poligons[2]->lightType = l3LightTypePoint;
            //obj01->poligons[2]->lightIntensity = 4;

            l3SetTransposeObject(b01, 0, 0, 0);
            l3SetScaleObject(b01, 0, 0, 0);
            //l3AddObjectToEnvironment(&env, b01, "box01");
        }
        double q, j;
        for (q = 0; q < 7; ++q)
        {
            double n = (q + 1.0) * 10.0;
            for (j = 0; j < n; ++j)
            {
                l3Object *b02 = l3CloneObject(b01); //クローン
                {
                    l3SetTransposeObject(b01, (q + 5.0) * 80 * cos(j / n * 2.0 * PI), 20.0, (q + 5.0) * 80 * sin(j / n * 2.0 * PI));
                    l3SetScaleObject(b01, 20 + (rand() % 5) * 5, 50 + (rand() % 10) * 20, 20 + (rand() % 5) * 5);
                    // l3AddObjectToEnvironment(&env, b02, "box02");
                }
            }
        }

        l3Object *obj3 = l3CreateObject();
        {
            l3AddVertexToObject(obj3, l3CreateVertex(0, 0, 0, &blue));
            l3Mat31A normal = {0, 1, 0}; // 正しい
            l3SetTransposeObject(obj3, 0, 0, 0);
            l3Poligon *poligons[] = {
                l3CreatePoligonPlane(0, normal),
            };
            poligons[0]->material = l3PoligonMaterialColor;
            poligons[0]->color.r = 60;
            poligons[0]->color.g = 60;
            poligons[0]->color.b = 60;
            poligons[0]->metalness[0] = poligons[0]->metalness[1] = poligons[0]->metalness[2] = 0.1;
            poligons[0]->roughness = radians(10);
            poligons[0]->roughnessSamples = 2;

            l3SetPoligonsToObject(obj3, sizeof(poligons) / sizeof(l3Poligon *), poligons);
            l3AddObjectToEnvironment(&env, obj3, "plane");
        }

        l3Object *sky = l3CreateObject();
        {
            l3Poligon *poligons[] = {
                l3CreatePoligonSky(),
            };
            poligons[0]->color.r = 20;
            poligons[0]->color.g = 20;
            poligons[0]->color.b = 20;
            poligons[0]->lightColor.r = 20;
            poligons[0]->lightColor.g = 20;
            poligons[0]->lightColor.b = 50;
            poligons[0]->lightType = l3LightTypeParallel;
            poligons[0]->lightIntensity = 1;
            poligons[0]->normal[0] = 1;
            poligons[0]->normal[1] = -1;
            poligons[0]->normal[2] = 1;
            l3NormarizeVec3(poligons[0]->normal, poligons[0]->normal);

            l3SetPoligonsToObject(sky, sizeof(poligons) / sizeof(l3Poligon *), poligons);
            l3AddObjectToEnvironment(&env, sky, "sky");
        }

        l3SetCameraInfoToEnvironment(&env, 500, 0, 700,
                                     0, 250, 0,
                                     0, 1, 0,
                                     radians(50), 2, 100000);

        l3MultithreadSequentialRenderer(&env, transition, options);
        // l3MultithreadRenderer(&env, options->renderer, transition, options->frames, options->threads);
        // l3MultithreadSequentialRenderer(&env, l3RasterizingRenderer, transition, 100, 16);

        l3DestructEnvironment(&env);
    }
    return 0;
}