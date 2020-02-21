#include "lib3d.h"

void l3SetOuterRectPoligon(l3Poligon* _poligon) {
    l3Type maxx = _poligon->vertices[0]->coordinate2d[0],
           maxy = _poligon->vertices[0]->coordinate2d[1],
           minx = _poligon->vertices[0]->coordinate2d[0],
           miny = _poligon->vertices[0]->coordinate2d[1];

    for (int i = 1; i < 3; i++) {
        if (_poligon->vertices[i]->coordinate2d[0] > maxx) maxx = _poligon->vertices[i]->coordinate2d[0];
        if (_poligon->vertices[i]->coordinate2d[1] > maxy) maxy = _poligon->vertices[i]->coordinate2d[1];
        if (_poligon->vertices[i]->coordinate2d[0] < minx) minx = _poligon->vertices[i]->coordinate2d[0];
        if (_poligon->vertices[i]->coordinate2d[1] < miny) miny = _poligon->vertices[i]->coordinate2d[1];
    }

    _poligon->max[0] = maxx;
    _poligon->max[1] = maxy;
    _poligon->min[0] = minx;
    _poligon->min[1] = miny;
}

l3Type l3GetTriangleArea(l3Mat21 p, l3Mat21 a, l3Mat21 b) {
    return fabs((a[0] - p[0]) * (b[1] - p[1]) - (a[1] - p[1]) * (b[0] - p[0])) / 2;
}
// Create Clone Destruct Clear(Initialize)

/**
 * ===========================================
 * Vertex
 * ===========================================
 */
l3Vertex* l3CreateVertex(l3Type x, l3Type y, l3Type z, l3RGB* color) {
    l3Vertex* _v = (l3Vertex*)calloc(sizeof(l3Vertex), 1);
    _v->coordinate[0] = x;
    _v->coordinate[1] = y;
    _v->coordinate[2] = z;
    _v->coordinate[3] = 1;
    _v->color.r = color->r;
    _v->color.g = color->g;
    _v->color.b = color->b;
    return _v;
}
l3Vertex* l3CloneVertex(l3Vertex* v) {
    l3Vertex* _v = (l3Vertex*)malloc(sizeof(l3Vertex));
    memcpy(_v, v, sizeof(l3Vertex));
    return _v;
}
void l3ClearVertices(int count, l3Vertex* vs[]) {
    while (count) vs[--count]->converted = false;
}
void l3ClearVertex(l3Vertex* v) {
    v->converted = false;
}

/**
 * ===========================================
 * Poligon
 * ===========================================
 */
l3Poligon* l3CreatePoligon(int v1, int v2, int v3) {
    l3Poligon* _p = (l3Poligon*)calloc(sizeof(l3Poligon), 1);
    _p->poligonType = l3PoligonTypeTriangle;
    _p->vertex_indices[0] = v1;
    _p->vertex_indices[1] = v2;
    _p->vertex_indices[2] = v3;
    _p->vertex_count = 3;
    return _p;
}

l3Poligon* l3CreatePoligonSphere(int center, int upper, l3Type radius) {
    l3Poligon* _p = (l3Poligon*)calloc(sizeof(l3Poligon), 1);
    _p->poligonType = l3PoligonTypeShpere;
    _p->vertex_indices[0] = center;
    _p->vertex_indices[1] = upper;
    _p->sphere_radius = radius;
    _p->vertex_count = 2;
    return _p;
}

/**
 * 平面オブジェクトを作成
 * point: 平面上の任意の点
 * normal: 平面の法線ベクトル（オモテウラなし）
 */
l3Poligon* l3CreatePoligonPlane(int point, l3Mat31 normal) {
    l3Poligon* _p = (l3Poligon*)calloc(sizeof(l3Poligon), 1);
    _p->poligonType = l3PoligonTypePlane;
    _p->vertex_indices[0] = point;
    _p->normal[0] = normal[0];
    _p->normal[1] = normal[1];
    _p->normal[2] = normal[2];
    _p->vertex_count = 1;
    // memcpy(_p->normal, normal, 3);
    return _p;
}
l3Poligon* l3CreatePoligonCircle(int point, l3Mat31 normal, l3Type radius) {
    l3Poligon* _p = (l3Poligon*)calloc(sizeof(l3Poligon), 1);
    _p->poligonType = l3PoligonTypePlane;
    _p->vertex_indices[0] = point;
    _p->normal[0] = normal[0];
    _p->normal[1] = normal[1];
    _p->normal[2] = normal[2];
    _p->sphere_radius = radius;
    _p->vertex_count = 1;
    // memcpy(_p->normal, normal, 3);
    return _p;
}

l3Poligon* l3CreatePoligonSky() {
    l3Poligon* _p = (l3Poligon*)calloc(sizeof(l3Poligon), 1);
    _p->poligonType = l3PoligonTypeSky;
    _p->vertex_count = 0;
    return _p;
}

l3Poligon* l3ClonePoligon(l3Poligon* p) {
    l3Poligon* _p = (l3Poligon*)malloc(sizeof(l3Poligon));
    memcpy(_p, p, sizeof(l3Poligon));
    if (p->textureVertices)
        _p->textureVertices = l3CloneMat(p->textureVertices, 2, 3);
    if (p->textureAffineMatInv)
        _p->textureAffineMatInv = l3CloneMat(p->textureAffineMatInv, 3, 3);
    if (p->texturePuv)
        _p->texturePuv = l3CloneMat(p->texturePuv, 2, 2);
    // textureは放置
    return _p;
}

l3Poligon* l3CreatePoligonColumn(int top, int end, l3Type radius) {
    l3Poligon* _p = (l3Poligon*)calloc(sizeof(l3Poligon), 1);
    _p->poligonType = l3PoligonTypeColumn;
    _p->vertex_indices[0] = top;
    _p->vertex_indices[1] = end;
    _p->sphere_radius = radius;
    _p->vertex_count = 2;
    return _p;
}

// destructはVertexごと、Poligonごとにやる？
void l3DestructPoligon(l3Poligon* p) {
    safe_free(p->textureVertices);
    safe_free(p->textureAffineMatInv);
    safe_free(p->texturePuv);
}

void l3ClearPoligon(l3Poligon* p) {
    // 実ポインタを初期化
    // memset(p->vertices, 0, l3POLIGON_VERTEX_COUNT * sizeof(l3Vertex*));
}
/**
 * ===========================================
 * Object
 * ===========================================
 */
void l3InitializeObject(l3Object* o) {
    o->sx = 1;
    o->sy = 1;
    o->sz = 1;
}

l3Object* l3CreateObject() {
    l3Object* _o = (l3Object*)calloc(sizeof(l3Object), 1);
    array_init(&_o->vertices, sizeof(l3Vertex*), true, 10);
    // array_expand(&_o->vertices, 10);
    l3InitializeObject(_o);
    return _o;
}

void l3ClearObject(l3Object* o) {
    for (int j = 0; j < o->poligon_count; j++) {
        l3ClearPoligon(o->poligons[j]);
    }
    for (int j = 0; j < (int)o->vertices.length; j++) {
        l3ClearVertex(array_at(&o->vertices, j));
    }
}

l3Object* l3CloneObject(l3Object* o) {
    l3Object* _o = (l3Object*)malloc(sizeof(l3Object));
    memcpy(_o, o, sizeof(l3Object));

    // poligons
    _o->poligons = (l3Poligon**)malloc(sizeof(l3Poligon*) * o->poligon_count);
    for (int i = 0; i < o->poligon_count; i++) {
        _o->poligons[i] = l3ClonePoligon(o->poligons[i]);
    }

    // vertices (array)
    _o->vertices.data = malloc(sizeof(l3Vertex*) * o->vertices.capacity);
    for (size_t i = 0; i < o->vertices.length; i++) {
        array_set(&_o->vertices, l3CloneVertex(array_at(&o->vertices, i)), i);
    }
    return _o;
}
void l3DestructObject(l3Object* o) {
    // vertices (array)
    array_each_i(&o->vertices, {
        if (array_ei) {
            free(array_ei);
        }
    });
    array_clear(&o->vertices);

    // poligon
    safe_free(o->poligons);
}

void l3SetTransposeObject(l3Object* o, l3Type dx, l3Type dy, l3Type dz) {
    o->dx = dx;
    o->dy = dy;
    o->dz = dz;
}

void l3SetScaleObject(l3Object* o, l3Type sx, l3Type sy, l3Type sz) {
    o->sx = sx;
    o->sy = sy;
    o->sz = sz;
}

void l3SetPoligonsToObject(l3Object* o, int count, l3Poligon* ps[]) {
    o->poligons = (l3Poligon**)malloc(sizeof(l3Poligon*) * count);
    memcpy(o->poligons, ps, sizeof(l3Poligon*) * count);
    o->poligon_count = count;
}

void l3SetCameraInfoToEnvironment(l3Environment* env,
                                  l3Type cx, l3Type cy, l3Type cz,
                                  l3Type tx, l3Type ty, l3Type tz,
                                  l3Type ux, l3Type uy, l3Type uz,
                                  l3Type angle, l3Type near, l3Type far) {
    env->camera.coordinate[0] = cx;
    env->camera.coordinate[1] = cy;
    env->camera.coordinate[2] = cz;
    env->camera.coordinate[3] = 1;
    env->camera.target[0] = tx;
    env->camera.target[1] = ty;
    env->camera.target[2] = tz;
    env->camera.target[3] = 1;
    env->camera.upper[0] = ux;
    env->camera.upper[1] = uy;
    env->camera.upper[2] = uz;
    env->camera.upper[3] = 1;
    env->camera.angle = angle;
    env->camera.near = near;
    env->camera.far = far;
}

/**
 * オブジェクトを追加、インデックスを返却
 * バウンディング半径を計算（原点からの距離の最大値）
 */
int l3AddObjectToEnvironment(l3Environment* env, l3Object* obj, const char* name) {
    obj->bounding_radius = l3GetBoundingRadius(obj);
    int index = array_push(&env->objects, obj);
    hashmap_add(&env->objects_map, name, (void*)(long)index);
    return index;
}

/**
 * 頂点を追加、インデックスを返却
 */
int l3AddVertexToObject(l3Object* obj, l3Vertex* v) {
    return array_push(&obj->vertices, v);
}

l3Object* l3GetObjectPtrEnvironment(l3Environment* env, int index) {
    return array_at(&env->objects, index);
}
l3Vertex* l3GetVertexPtrObject(l3Object* obj, int index) {
    return array_at(&obj->vertices, index);
}

/**
 * すべてのオブジェクトに対して、すべてのポリゴンに格納された頂点のインデックスから実ポインタを算出する
 */
void l3SolvePtrsEnvironment(l3Environment* env) {
    for (size_t i = 0; i < env->objects.length; i++) {
        l3Object* object = array_at(&env->objects, i);
        for (int j = 0; j < object->poligon_count; j++) {
            l3Poligon* poligon = object->poligons[j];
            for (int k = 0; k < l3POLIGON_VERTEX_COUNT; k++) {
                poligon->vertices[k] = l3GetVertexPtrObject(object, poligon->vertex_indices[k]);
            }
            // ここでポリゴンの一覧を作る
            array_push(&env->poligons, poligon);  //free(): invalid pointer
        }
    }
}

/**
 * ===========================================
 * Environment
 * ===========================================
 */
void l3InitializeEnvironment(l3Environment* env) {
    memset(env, 0, sizeof(l3Environment));
    array_init(&env->objects, sizeof(l3Object*), true, 10);
    array_init(&env->poligons, sizeof(l3Poligon*), true, 10);
    hashmap_init(&env->objects_map, 10);
}

void l3ClearEnvironment(l3Environment* env) {
    for (size_t i = 0; i < env->objects.length; i++) {
        l3Object* object = array_at(&env->objects, i);
        l3ClearObject(object);
    }
}

void l3DestructEnvironment(l3Environment* env) {
    array_each_i(&env->objects, {
        if (array_ei) {
            l3DestructObject(array_ei);
            free(array_ei);
            array_ei = NULL;
        }
    });
    array_clear(&env->objects);
    array_clear(&env->poligons);
    hashmap_destruct(&env->objects_map);
}

l3Environment* l3CloneEnvironment(l3Environment* env) {
    l3Environment* _env = (l3Environment*)calloc(sizeof(l3Environment), 1);
    memcpy(_env, env, sizeof(l3Environment));

    _env->objects.data = malloc(sizeof(l3Object*) * _env->objects.capacity);
    for (size_t i = 0; i < env->objects.length; i++) {
        array_set(&_env->objects, l3CloneObject(array_at(&env->objects, i)), i);
    }

    // これをしないと他のスレッドのメモリを開放しようとしてしまう
    _env->poligons.data = calloc(sizeof(l3Poligon*), _env->poligons.capacity);

    hashmap_init(&_env->objects_map, env->objects_map.capacity);
    hashmap_each_i(&env->objects_map, {
        hashmap_add(&_env->objects_map, hashmap_ei->key, hashmap_ei->ptr);
    });

    return _env;
}
l3Object* l3FindObject(l3Environment* env, const char* name) {
    int index = (int)(long)hashmap_find(&env->objects_map, name);
    return array_at(&env->objects, index);
}

// =============================================
// l3Ray
// =============================================
// void l3InitializeRay(l3Ray* ray) {
//     memset(ray, 0, sizeof(l3Ray));
// }