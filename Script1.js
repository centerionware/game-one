// This chunk of code is hearby designated as the terrain loader, handler, and displayer. All things related to terrain.

// First, load that texture map..

var texture_map = THREE.ImageUtils.loadTexture("/download.business_cgi/Game-One/Games?MB_FILEGET=1007");
texture_map.wrapS = THREE.RepeatWrapping;
texture_map.wrapT = THREE.RepeatWrapping;

// Each face makes a plane.
// There are only 2 face uv's needed, since only 2 triangles are drawn.
// 8 vertices per cube..
// 12 faces per cube (2 triangles per quad... fucking triangles. what is this, 1993? Stupid opengles.)
// gen_faces contains them in a specific order so that face_normals can be reused
// 6 face normals. each face_normal is used for 2 triangles.

var gen_faceVertexUVS = [[[0, 1], [0, 0], [1, 1]], [[0, 0], [1, 0], [1, 1]]];
var gen_vertices = [[1, 1, 1], [1, 1, -1], [1, -1, 1], [1, -1, -1], [-1, 1, -1], [-1, 1, 1], [-1, -1, -1], [-1, -1, 1]];
var gen_faces = [[0, 2, 1], [2, 3, 1], [4, 6, 5], [6, 7, 5], [4, 5, 1], [5, 0, 1], [7, 6, 2], [6, 3, 2], [5, 7, 0], [7, 2, 0], [1, 3, 4], [3, 6, 4]];

var face_normals = [[1, 0, 0], [-1, 0, 0], [0, 1, 0], [0, -1, 0], [0, 0, 1], [0, 0, -1]];

var neighbor_list = function (idx) {
    var position = idx_to_vec3(idx.id, extract_chunk_position(idx.chunk));
    // This position should be relative to the chunk center.
    var offset = new THREE.Vector3(31, 961, 1);

    // idx = parseInt(idx);

    var nl = [
        new THREE.Vector3(-1.0, -1.0, -1.0), new THREE.Vector3(-1.0, -1.0, 0.0), new THREE.Vector3(-1.0, -1.0, 1.0),//  0,1,2    -> 0,3,6
        new THREE.Vector3(-1.0, 0.0, -1.0), new THREE.Vector3(-1.0, 0.0, 0.0), new THREE.Vector3(-1.0, 0.0, 1.0),   //  3,4,5    -> 9,12,15 
        new THREE.Vector3(-1.0, 1.0, -1.0), new THREE.Vector3(-1.0, 1.0, 0.0), new THREE.Vector3(-1.0, 1.0, 1.0),   //  6,7,8    -> 18,21,24

        new THREE.Vector3(0.0, -1.0, -1.0), new THREE.Vector3(0.0, -1.0, 0.0), new THREE.Vector3(0.0, -1.0, 1.0),  //   9,10,11  -> 1,4,7
        new THREE.Vector3(0.0, 0.0, -1.0), new THREE.Vector3(0.0, 0.0, 0.0), new THREE.Vector3(0.0, 0.0, 1.0),     //   12,13,14 -> 10,13,16
        new THREE.Vector3(0.0, 1.0, -1.0), new THREE.Vector3(0.0, 1.0, 0.0), new THREE.Vector3(0.0, 1.0, 1.0),     //   15,16,17 -> 19,22,25

        new THREE.Vector3(1.0, -1.0, -1.0), new THREE.Vector3(1.0, -1.0, 0.0), new THREE.Vector3(1.0, -1.0, 1.0),  //   18,19,20 -> 2,5,8
        new THREE.Vector3(1.0, 0.0, -1.0), new THREE.Vector3(1.0, 0.0, 0.0), new THREE.Vector3(1.0, 0.0, 1.0),     //   21,22,23 -> 11,14,17
        new THREE.Vector3(1.0, 1.0, -1.0), new THREE.Vector3(1.0, 1.0, 0.0), new THREE.Vector3(1.0, 1.0, 1.0)      //   24,25,26 -> 20,23,26
    ];
    var ret = [];
    for (var i = 0; i < 27; i++) {
        ret.push(0);
        var npos = nl[i];
        npos.add(position);
        var ce = active_terrain.has_chunk(position_from_vec3(npos));
        var active_chunk = idx.chunk;
        if (ce != false && ce != active_chunk.id) {
            var the_chunk;
            for (c in active_terrain.chunks) {
                if (active_terrain.chunks[c].id == ce)
                    active_chunk = active_terrain.chunks[c];
            }

        }
        if (typeof (active_chunk.volumes) != "undefined" && String(to_idx(npos, extract_chunk_position(active_chunk))) in active_chunk.volumes) {
            ret[ret.length - 1] = active_chunk.volumes[String(to_idx(npos, extract_chunk_position(active_chunk)))];
        }

    }

    return ret;
}

var vec_dist = function (pointa, pointb) {
    return Math.sqrt(Math.pow((pointb.x - pointa.x), 2) + Math.pow(pointb.y - pointa.y, 2) + Math.pow(pointb.z - pointa.z, 2));
}
var idsTouching = function (point, chunk, neighbors) {
    var ids = [];
    for (var i = 0; i < neighbors.length; i++) {
        if (i == 13) continue;
        if (neighbors[i] == 0) continue;
        var nidx = neighbors[i];
        var npos = idx_to_vec3(nidx.id, extract_chunk_position(nidx.chunk));
        var distance = vec_dist(point, npos);
        if (distance <= .9 && distance >= -.9) {
            ids.push(nidx);
        }
    }
    return ids;
}
var touching_vertex_id = function (other_position, idx) {

    var ffs = [];
    for (var i = 0; i < 8; i++) ffs.push(new THREE.Vector3(gen_vertices[i][0] * .5, gen_vertices[i][1] * .5, gen_vertices[i][2] * .5));
    var new_verts = ffs;
    var position = idx_to_vec3(idx.id, extract_chunk_position(idx.chunk));
    for (var i = 0; i < 8; i++) {
        var vertRealLocation = new THREE.Vector3(new_verts[i].x, new_verts[i].y, new_verts[i].z);
        vertRealLocation.add(new THREE.Vector3(position.x, position.y, position.z));
        if (other_position.equals(vertRealLocation)) { return i; }
    }
    return -1;
}
var gen_combined_mesh_maker = function (idx, chunk) {
    var position = idx_to_vec3(idx, extract_chunk_position(chunk));
    var relative_position = idx_to_vec3(idx, new THREE.Vector3(0, 0, 0));
    var neighbors = neighbor_list(chunk.volumes[String(idx)]);
    var volume = chunk.volumes[String(idx)];
    {
        var cull_check = [9, 12, 15, 10, 16, 11, 14, 17];
        var cull = true;
        for (var i = 0; i < cull_check.length; i++) if (neighbors[cull_check] != 0) { cull = false; break; }
        if (cull) return;
    }



    var offVerts = function (neighbors, cubeVerts) {
        //return;
        if (!neighbors[1] && !neighbors[2] && !neighbors[4] && !neighbors[5]) { cubeVerts[5].x = cubeVerts[0].x * 0.15; }
        if (!neighbors[1] && !neighbors[2] && !neighbors[10] && !neighbors[11]) { cubeVerts[5].y = cubeVerts[0].y * 0.15; }
        if (!neighbors[2] && !neighbors[5] && !neighbors[11] && !neighbors[14]) { cubeVerts[5].z = cubeVerts[0].z * 0.15; }
        if (!neighbors[4] && !neighbors[5] && !neighbors[7] && !neighbors[8]) { cubeVerts[7].x = cubeVerts[1].x * 0.15; }
        if (!neighbors[7] && !neighbors[8] && !neighbors[16] && !neighbors[17]) { cubeVerts[7].y = cubeVerts[1].y * 0.15; }
        if (!neighbors[5] && !neighbors[8] && !neighbors[14] && !neighbors[17]) { cubeVerts[7].z = cubeVerts[1].z * 0.15; }
        if (!neighbors[0] && !neighbors[1] && !neighbors[3] && !neighbors[4]) { cubeVerts[4].x = cubeVerts[2].x * 0.15; }
        if (!neighbors[0] && !neighbors[1] && !neighbors[9] && !neighbors[10]) { cubeVerts[4].y = cubeVerts[2].y * 0.15; }
        if (!neighbors[0] && !neighbors[3] && !neighbors[9] && !neighbors[12]) { cubeVerts[4].z = cubeVerts[2].z * 0.15; }
        if (!neighbors[3] && !neighbors[4] && !neighbors[6] && !neighbors[7]) { cubeVerts[6].x = cubeVerts[3].x * 0.15; }
        if (!neighbors[6] && !neighbors[7] && !neighbors[15] && !neighbors[16]) { cubeVerts[6].y = cubeVerts[3].y * 0.15; }
        if (!neighbors[3] && !neighbors[6] && !neighbors[12] && !neighbors[15]) { cubeVerts[6].z = cubeVerts[3].z * 0.15; }
        if (!neighbors[19] && !neighbors[20] && !neighbors[22] && !neighbors[23]) { cubeVerts[3].x = cubeVerts[4].x * 0.15; }
        if (!neighbors[10] && !neighbors[11] && !neighbors[19] && !neighbors[20]) { cubeVerts[3].y = cubeVerts[4].y * 0.15; }
        if (!neighbors[11] && !neighbors[14] && !neighbors[20] && !neighbors[23]) { cubeVerts[3].z = cubeVerts[4].z * 0.15; }
        if (!neighbors[22] && !neighbors[23] && !neighbors[25] && !neighbors[26]) { cubeVerts[1].x = cubeVerts[5].x * 0.15; }
        if (!neighbors[16] && !neighbors[17] && !neighbors[25] && !neighbors[26]) { cubeVerts[1].y = cubeVerts[5].y * 0.15; }
        if (!neighbors[14] && !neighbors[17] && !neighbors[23] && !neighbors[26]) { cubeVerts[1].z = cubeVerts[5].z * 0.15; }
        if (!neighbors[18] && !neighbors[19] && !neighbors[21] && !neighbors[22]) { cubeVerts[2].x = cubeVerts[6].x * 0.15; }
        if (!neighbors[9] && !neighbors[10] && !neighbors[18] && !neighbors[19]) { cubeVerts[2].y = cubeVerts[6].y * 0.15; }
        if (!neighbors[9] && !neighbors[12] && !neighbors[18] && !neighbors[21]) { cubeVerts[2].z = cubeVerts[6].z * 0.15; }
        if (!neighbors[21] && !neighbors[22] && !neighbors[24] && !neighbors[25]) { cubeVerts[0].x = cubeVerts[7].x * 0.15; }
        if (!neighbors[15] && !neighbors[16] && !neighbors[24] && !neighbors[25]) { cubeVerts[0].y = cubeVerts[7].y * 0.15; }
        if (!neighbors[12] && !neighbors[15] && !neighbors[21] && !neighbors[24]) { cubeVerts[0].z = cubeVerts[7].z * 0.15; }
        return cubeVerts;
    }


    // Well, instead of all that crap.. 
    // MMkay..
    var geometry = chunk.geometry; // new THREE.Geometry(); // No no.. The geometry goes on the chunk.
    var gen_verts = gen_vertices; // copy gen_vertices..

    gen_verts = offVerts(neighbors, gen_verts);
    volume.cubeVerts = [];


    var next_insert_id = geometry.vertices.length;
    var ffs = [];
    for (var i = 0; i < 8; i++) ffs.push(new THREE.Vector3(gen_vertices[i][0] * .5, gen_vertices[i][1] * .5, gen_vertices[i][2] * .5));
    var new_verts = ffs;//offVerts(neighbors, ffs);

    for (var i = 0; i < 8; i++) {
        var vertRealLocation = new THREE.Vector3(new_verts[i].x, new_verts[i].y, new_verts[i].z);
        vertRealLocation.add(new THREE.Vector3(position.x, position.y, position.z));
        //        vertRealLocation.add(relative_position);
        var ids_touching = idsTouching(vertRealLocation, chunk, neighbors);
        if (ids_touching.length < 1) {
            var smaller_vert = new THREE.Vector3(gen_vertices[i][0] * .5 * .15, gen_vertices[i][1] * .5 * .15, gen_vertices[i][2] * .5 * .15);
            vertRealLocation = new THREE.Vector3(smaller_vert.x, smaller_vert.y, smaller_vert.z);
            vertRealLocation.add(new THREE.Vector3(position.x, position.y, position.z));
        }
        var merged = false;
        for (var j = 0; j < ids_touching.length && !merged; j++) {
            if (typeof (ids_touching[j].drawn) != 'undefined' && ids_touching[j].drawn && ids_touching[j].chunk.id == chunk.id) {
                // Merge the vertices.
                var othervertid = touching_vertex_id(vertRealLocation, ids_touching[j]);
                if (othervertid != -1) {
                    merged = true;
                    var overt =
                    volume.cubeVerts.push({ 'vert': vertRealLocation, 'vertid': ids_touching[j].cubeVerts[othervertid].vertid, 'ids_touching': ids_touching });
                    console.log("Merging vertex");
                }
            }
        }
        if (!merged) {
            geometry.vertices.push(vertRealLocation);
            volume.cubeVerts.push({ 'vert': vertRealLocation, 'vertid': next_insert_id, 'ids_touching': ids_touching })
            next_insert_id++;
        }

    }
    // Now that the verts are made and geometry stored.. Need to make faces from the verts.
    for (var i = 0; i < 6; i++) {
        var first = i * 2;
        var second = first + 1;

        var verta = new THREE.Vector3(volume.cubeVerts[gen_faces[first][0]].vertid, volume.cubeVerts[gen_faces[first][1]].vertid, volume.cubeVerts[gen_faces[first][2]].vertid);
        var vertb = new THREE.Vector3(volume.cubeVerts[gen_faces[second][0]].vertid, volume.cubeVerts[gen_faces[second][1]].vertid, volume.cubeVerts[gen_faces[second][2]].vertid);

        var vertia = geometry.vertices[verta.x];
        var vertib = geometry.vertices[verta.y];
        var vertic = geometry.vertices[verta.z];
        var draw_faces = true;
        if (vertia.x == vertib.x && vertib.x == vertic.x) { if (vertia.x > position.x) { if (neighbors[22] != 0) draw_faces = false; } else { if (neighbors[4] != 0) draw_faces = false; } }
        if (vertia.y == vertib.y && vertib.y == vertic.y) { if (vertia.y > position.y) { if (neighbors[16] != 0) draw_faces = false; } else { if (neighbors[10] != 0) draw_faces = false; } }
        if (vertia.z == vertib.z && vertib.z == vertic.z) { if (vertia.z > position.z) { if (neighbors[14] != 0) draw_faces = false; } else { if (neighbors[12] != 0) draw_faces = false; } }
        if (!draw_faces) {
            //console.log("Skipping face..");
        }
        if (draw_faces) {
            var normal = new THREE.Vector3(face_normals[i][0], face_normals[i][1], face_normals[i][2]);
            var rgba = new THREE.Color(1, 1, 1);
            var face_a = new THREE.Face3(verta.x, verta.y, verta.z, normal, rgba, 0);
            var face_b = new THREE.Face3(vertb.x, vertb.y, vertb.z, normal, rgba, 0);
            //var faceuvs = [];
            for (var j = 0; j < 2; j++) {
                var vertuvs = [];
                vertuvs.push(new THREE.Vector2(gen_faceVertexUVS[j][0][0], gen_faceVertexUVS[j][0][1]));
                vertuvs.push(vuvb = new THREE.Vector2(gen_faceVertexUVS[j][1][0], gen_faceVertexUVS[j][1][1]));
                vertuvs.push(vuvc = new THREE.Vector2(gen_faceVertexUVS[j][2][0], gen_faceVertexUVS[j][2][1]));
                vertuvs = replace_vert_uvs(vertuvs, getUv(volume.texid));
                geometry.faceVertexUvs[0].push(vertuvs);
                //faceuvs.push(vertuvs);
            }
            // There's got to be a simpler way..
            //geometry.faces.push(face_b);
            geometry.faces.push(face_a);
            geometry.faces.push(face_b);

        }
    }
    volume.drawn = true;

}

function mergeMeshes(meshes) {
    console.log("Warning, this should no longer be used!");
    var combined = new THREE.Geometry();
    for (var i = 0; i < meshes.length; i++) {
        meshes[i].updateMatrix();
        combined.merge(meshes[i].geometry, meshes[i].matrix);
        // meshes[i].dispose();
        delete meshes[i];
        // console.log(typeof(meshes[i]));
    }
    delete meshes;
    return combined;
}

var selected_texture = 59;
/* This isn't really used since the class itself is defined by json.. woot. but this is kinda what it should look like....
function Chunk(id,text_description,position) {
  this.id = id;
  this.position = position;
  this.volumes = [];
  this.description=text_description;
}
Chunk.prototype.add_volumeid(id,texid) {
  this.volumes.push({'id':id,'texid':texid});
}
Chunk.prototype.update(json_obj) {
  var parsed =  $.parseJSON(json_obj); // Contains all the volumes
  this.volumes = parsed.volumes;
}

*/
var lm_base = new THREE.Vector3(15, 30, 15);

function to_idx(vector, chunk_position) {
    var i = 31;
    var j = i * i;
    var tmp_v = new THREE.Vector3(0, 0, 0);
    tmp_v.add(vector);
    tmp_v.sub(chunk_position);
    tmp_v.add(lm_base);

    var idx = Math.floor(Math.floor((tmp_v.y * j)) + Math.floor((tmp_v.x * i)) + Math.floor(tmp_v.z));
    return idx;
}
function idx_to_vec3(idx, chunk_position) {
    var j = 31;
    var k = j * j;
    var y = Math.floor(idx / k);
    var x = Math.floor((idx - y * k) / j);
    var z = Math.floor((idx - y * k - x * j));

    var vec = new THREE.Vector3(x, y, z);
    vec.add(chunk_position);
    vec.sub(lm_base);
    return vec;
}
function position_from_vec3(v) {

    var cv = new THREE.Vector3(0.0, 0.0, 0.0);
    if (v.x > 0.0) while ((cv.x - v.x) + 15.0 < 0.0) cv.x += 31.0;
    else while ((cv.x - v.x) + 15.0 > 30.0) cv.x -= 31.0;
    if (v.y > 0.0) while ((cv.y - v.y) + 30.0 < 0.0) cv.y += 61.0;
    else while ((cv.y - v.y) + 30.0 > 60.0) cv.y -= 61.0;
    if (v.z > 0.0) while ((cv.z - v.z) + 15.0 < 0.0) cv.z += 31.0;
    else while ((cv.z - v.z) + 15.0 > 30.0) cv.z -= 31.0;
    return cv;
}
function terrain_handler() {
    this.chunks = [];
}
function extract_chunk_position(chunk) {
    return new THREE.Vector3(parseFloat(chunk.x), parseFloat(chunk.y), parseFloat(chunk.z));
}

terrain_handler.prototype.chunk_position = function (chunk_id) {
    for (var i = 0; i < this.chunks.length; i++) if (this.chunks[i].id == chunk_id) return extract_chunk_position(this.chunks[i]);
    return false;
}
terrain_handler.prototype.super_basic_display_all_chunks = function () {
    for (var i = 0; i < this.chunks.length; i++)
        for (vol in this.chunks[i].volumes.length) {
            var meshes = expandVolumesToCubes(idx_to_vec3(parseFloat(this.chunks[i].volumes[vol].id), extract_chunk_position(this.chunks[i])));
            meshes.forEach(function (c) {
                c.updateMatrix(); c.matrixAutoUpdate = false;
                merge_volumetric(c);
            });
        }

}

terrain_handler.prototype.chunkid_has_vidx = function (chunkid, idx) {
    for (var i = 0; i < this.chunks.length; i++)
        if (this.chunks[i].id == chunkid)
            for (vol in this.chunks[i].volumes)
                if (this.chunks[i].volumes[vol].id == idx)
                    return true;
    return false;
}


terrain_handler.prototype.ind_chunk_disp = function (chunk) {

    // So this whole thing creates seperate geometry for each cube. Instead, I need to go ahead and manually create each vertex in order,
    // create the faces, then create the uv's, and add them to the chunks geometry object directly.

    var display_individual_cube = function (position) { // right now this is a copy of expandSingleVolume
        var BMat = new THREE.MeshBasicMaterial({ map: texture_map });
        var BGeom = new THREE.BoxGeometry(1, 1, 1);
        var newFaceVertexUvs = replace_face_uvs(BGeom.faceVertexUvs, getUv(position.texid));

        delete BGeom.faceVertexUvs;
        BGeom.faceVertexUvs = newFaceVertexUvs;
        var mesh = new THREE.Mesh(BGeom, BMat);
        mesh.position.set(position.x, position.y, position.z);// = position;
        return mesh;
    }

    var display_cube_list = function (positions, cube_expander) { // pass display_individual_cube as cube_expander fist...
        var meshes = new Array();
        positions.forEach(
          function (c, i, a) {
              this.push(cube_expander(c));
          }, meshes);
        return meshes;
    }
    var positions = [];
    chunk.geometry = new THREE.Geometry();
    for (vol in chunk.volumes) {
        //        the_position = idx_to_vec3(parseFloat(chunk.volumes[i].id), extract_chunk_position(chunk),chunk.volumes[i].texid);
        gen_combined_mesh_maker(parseInt(chunk.volumes[vol].id), chunk);
    }

    var NVOLUME_Geometry = chunk.geometry;
    if (typeof (chunk.three_renderer) != 'undefined') {
        // Destroy the old geometry and redraw it. Remove it from the scene first.
        //          chunk.three_renderer.Geometry.dispose(); // cleanup?
        scene.remove(scene.getObjectByName("mb_chunk_" + String(chunk.id)));

        chunk.three_renderer.Geometry = NVOLUME_Geometry;
        chunk.three_renderer.Mesh = new THREE.Mesh(chunk.three_renderer.Geometry, chunk.three_renderer.Material);
        chunk.three_renderer.Mesh.name = "mb_chunk_" + String(chunk.id);
        scene.add(chunk.three_renderer.Mesh);
    } else {
        chunk.three_renderer = new Object();
        chunk.three_renderer.Geometry = NVOLUME_Geometry;
        chunk.three_renderer.Geometry.dynamic = true;
        chunk.three_renderer.Material = new THREE.MeshBasicMaterial({ map: texture_map });
        chunk.three_renderer.Mesh = new THREE.Mesh(chunk.three_renderer.Geometry, chunk.three_renderer.Material);
        chunk.three_renderer.Mesh.name = "mb_chunk_" + String(chunk.id);
        scene.add(chunk.three_renderer.Mesh);
    }
    delete positions;
    delete meshes;
}
terrain_handler.prototype.display_chunk = function (idx) {
    for (var i = 0; i < this.chunks.length; i++) if (this.chunks[i].id == idx) this.ind_chunk_disp(this.chunks[i]);
}
terrain_handler.prototype.has_chunk = function (vector) {
    p = position_from_vec3(vector);
    for (var i = 0; i < this.chunks.length; i++) if (this.chunks[i].x == p.x && this.chunks[i].y == p.y && this.chunks[i].z == p.z) return this.chunks[i].id;
    return false;
}
var ltime = false;
var needs_update = [];


var add_chunk_to_update = function (e) {
    if (indexOf.call(needs_update, e.id) < 0) needs_update.push(e.id);
    if (ltime != false) clearTimeout(ltime);
    ltime = setTimeout(function () {
        for (var i = 0; i < needs_update.length; i++)
            ws.send("/ccd2 " + needs_update[i]);
        needs_update = [];
    }, 1000);// Limit updates to once a second.
}

terrain_handler.prototype.update_chunk = function (e) {
    this.parsing = e;
    this.handled = false;
    this.found = false;
    this.chunks.forEach(function (cv, i, a) { if (this.parsing.id == cv.id) this.found = cv; }, this);
    if (this.found == false) {
        this.chunks.push(e);

    }
    else {
        cv = e;
    }
    add_chunk_to_update(e);
}
terrain_handler.prototype.update_individual_chunk = function (e) {
    this.parsing = e;
    this.handled = false;
    this.found = false;
    this.chunks.forEach(function (cv, i, a) { if (this.parsing.id == cv.id) this.found = cv; }, this);
    if (this.found == false) {
        // Cannot insert a chunk from e, they're not the same thing.
        //   this.chunks.push(e);
        //   this.chunks[this.chunks.length-1].volumes = 
        // This shouldn't happen..
        alert('update_individual_chunk was called without the chunk first existing. It should be added via update_chunk first!');
    }
    else {
        this.found.volumes = e.volumes;
        for (c in this.found.volumes) {
            this.found.volumes[c].chunk = this.found;
        }
    }
    // this.display_chunk(e.id)
}
terrain_handler.prototype.rerender_chunk = function (chunk) {
    if (chunk.geometry.vertices.length == 0) return;
    var NVOLUME_Geometry = new THREE.BufferGeometry();//(chunk.geometry);

    NVOLUME_Geometry.fromGeometry(chunk.geometry);
    NVOLUME_Geometry = new THREE.Geometry().fromBufferGeometry(NVOLUME_Geometry);
    if (typeof (chunk.three_renderer) != 'undefined') {
        // Destroy the old geometry and redraw it. Remove it from the scene first.
        //          chunk.three_renderer.Geometry.dispose(); // cleanup?
        scene.remove(scene.getObjectByName("mb_chunk_" + String(chunk.id)));

        chunk.three_renderer.Geometry = NVOLUME_Geometry;
        chunk.three_renderer.Mesh = new THREE.Mesh(chunk.three_renderer.Geometry, chunk.three_renderer.Material);
        chunk.three_renderer.Mesh.name = "mb_chunk_" + String(chunk.id);
        scene.add(chunk.three_renderer.Mesh);
    } else {
        chunk.three_renderer = new Object();
        chunk.three_renderer.Geometry = NVOLUME_Geometry;
        chunk.three_renderer.Geometry.dynamic = true;
        chunk.three_renderer.Material = new THREE.MeshBasicMaterial({ map: texture_map });
        chunk.three_renderer.Mesh = new THREE.Mesh(chunk.three_renderer.Geometry, chunk.three_renderer.Material);
        chunk.three_renderer.Mesh.name = "mb_chunk_" + String(chunk.id);
        scene.add(chunk.three_renderer.Mesh);
    }
}
terrain_handler.prototype.ww_update_individual_chunk = function (e) {
    for (var i = 0; i < this.chunks.length; i++) {
        if (this.chunks[i].id == e.id) {
            if (typeof (this.chunks[i].three_renderer) != 'undefined') e.three_renderer = this.chunks[i].three_renderer;
            this.chunks[i] = e; // Copy in the new details, erase the old chunk.
            this.rerender_chunk(this.chunks[i]);
        }
    }
}
var display_rendered_chunk = function (chunk) {
    worker.postMessage({ 'mode': 'debug_stop' });
    active_terrain.ww_update_individual_chunk(chunk);
    for (var i = 0; i < active_terrain.chunks.length; i++) {
        if (active_terrain.chunks[i].id == chunk.id) {
            active_terrain.chunks[i] = chunk; // Copy in the new details, erase the old chunk.
        }
    }

}
var active_terrain = new terrain_handler();

var update_chunks = function (e) {
    worker.postMessage({ 'mode': 'updatechunk', 'chunk': e })
    var parsed = $.parseJSON(e);
    active_terrain.update_chunk(parsed)
}
var update_individual_chunk = function (e) {
    worker.postMessage({ 'mode': 'ind_updatechunk', 'chunk': e })
    var parsed = $.parseJSON(e);
    active_terrain.update_individual_chunk(parsed);
}
var chunk_update_notification = function (e) {

    id = parseInt(e); // send an update request, but only if we actually have that chunk loaded.. Unload chunks after they're X chunk distance away from the player.
    active_terrain.chunks.forEach(function (cv, i, a) { if (this == cv.id) add_chunk_to_update(cv); }, id);
}






/*	if(control_bit == '3')
                update_chunks(received_msg); // received_msg is a json object.
        if(control_bit == '4')
                update_individual_chunk(received_msg);
        if(control_bit == '5')
                chunk_update_notification(received_msg);
*/

// Create a canvas from the image.
// Because the texture map is 1024x1024, each image in the atlas uses exactly 1/8th of the atlas, the uv's can be easily calculated.
// I should consider using 1/16th per image, but for now 8x8 is enough
function getUv(index) {
    var w = 16;
    var image_size = 1024;// image should be x==y, so 1024x1024..
    if (index > w * w) index = 0;
    var u = 0;
    var v = 0;
    while (index > w - 1) { v += 1; index -= w; }
    u = index;
    // Now u contains the image along the x axis, v contains the image along the y axis
    u = u / w; v = v / w;
    var offset = 1 / (w * 2); // because it's 1/2 of 1/8th..

    u += offset; v += offset;
    offset -= 1 / (image_size * 4);

    // Now it's normalized between 0-1. now the actual uv's can be calculated
    return [new THREE.Vector2(u - offset, v - offset), new THREE.Vector2(u + offset, v - offset), new THREE.Vector2(u + offset, v + offset), new THREE.Vector2(u - offset, v + offset)];
}

function get_closest_uv(uvs, vertuv) {
    var closest = 0;
    var cdist = 100;
    for (var i = 0; i < uvs.length; i++) {
        var ldist = Math.sqrt(Math.pow(uvs[i].x - vertuv.x, 2) + Math.pow(uvs[i].y - vertuv.y, 2));
        if (ldist < cdist) { closest = i; cdist = ldist; }
    }
    return uvs[closest];
}
function replace_vert_uvs(vertexuvs, uvs) {
    for (var i = 0; i < vertexuvs.length; i++) {
        vertexuvs[i] = get_closest_uv(uvs, vertexuvs[i]);
    }
    return vertexuvs;
}
function replace_face_uvs(faceuvs, uvs) {
    for (var i = 0; i < faceuvs[0].length; i++) {
        faceuvs[0][i] = replace_vert_uvs(faceuvs[0][i], uvs);
    }
    return faceuvs;
}

//return array with height data from img
function getVolumePoints() {
    var ret = new Array();
    ret.push(new THREE.Vector3(0, 0, 0));
    return ret;
}


/*
var VOLUME_Geometry = new THREE.Geometry();
var VOLUME_Material = new THREE.MeshBasicMaterial( { map:texture_map });
var VOLUME_Mesh = new THREE.Mesh(VOLUME_Geometry, VOLUME_Material);
var VOLUME_Active = false;
*/
function merge_volumetric(other) {
    scene.add(other);
}

function expandSingleVolume(position) {
    var BGeom = new THREE.BoxGeometry(1, 1, 1);
    var BMat = new THREE.MeshBasicMaterial({ map: texture_map });
    BGeom.faceVertexUvs = replace_face_uvs(BGeom.faceVertexUvs, getUv(selected_texture));
    var mesh = new THREE.Mesh(BGeom, BMat);
    mesh.position.set(position.x, position.y, position.z);// = position;
    return mesh;
}
function expandVolumesToCubes(positions) {
    var meshes = new Array();
    positions.forEach(
      function (c, i, a) {
          this.push(expandSingleVolume(c));
      }, meshes);
    return meshes;
}
function initialize_volume_terrain() {
    var meshes = expandVolumesToCubes(getVolumePoints());
    meshes.forEach(function (c) { merge_volumetric(c); });
}
initialize_volume_terrain(); // This is still called just in case everything is erased from the db. It adds a default point at 0,0,0 on which to draw from.


/* The stuff for the selection cursor.. Make it transparent somehow */
var sel_cur_box = new THREE.BoxGeometry(1, 1, 1);
var sel_cur_mat = new THREE.MeshBasicMaterial({ map: texture_map });
sel_cur_box.faceVertexUvs = replace_face_uvs(sel_cur_box.faceVertexUvs, getUv(58));
var Selection_Cursor = new THREE.Mesh(sel_cur_box, sel_cur_mat);
Selection_Cursor.material.opacity = .3;
Selection_Cursor.material.transparent = true;
Selection_Cursor.position.set(-1000, -1000, -1000);

scene.add(Selection_Cursor);