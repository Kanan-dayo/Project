xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 353;
 -17.14500;38.71883;-3.45593;,
 17.14500;38.71883;-3.45593;,
 17.14500;27.74883;-3.45593;,
 -17.14500;27.74883;-3.45593;,
 17.14500;38.71883;-3.45593;,
 17.14500;38.71883;-2.10593;,
 17.14500;27.74883;-2.10593;,
 17.14500;27.74883;-3.45593;,
 17.14500;38.71883;-2.10593;,
 -17.14500;38.71883;-2.10593;,
 -17.14500;27.74883;-2.10593;,
 17.14500;27.74883;-2.10593;,
 -17.14500;38.71883;-2.10593;,
 -17.14500;38.71883;-3.45593;,
 -17.14500;27.74883;-3.45593;,
 -17.14500;27.74883;-2.10593;,
 17.14500;38.71883;-3.45593;,
 -17.14500;38.71883;-3.45593;,
 -17.14500;27.74883;-3.45593;,
 17.14500;27.74883;-3.45593;,
 -7.79292;36.54383;-4.59802;,
 -7.20165;36.54383;-4.23483;,
 -7.20165;29.71383;-4.23483;,
 -7.79292;29.71383;-4.59802;,
 -6.95673;36.54383;-3.35802;,
 -6.95673;29.71383;-3.35802;,
 -7.20165;36.54383;-2.48120;,
 -7.20165;29.71383;-2.48120;,
 -7.79292;36.54383;-2.11802;,
 -7.79292;29.71383;-2.11802;,
 -8.38419;36.54383;-2.48120;,
 -8.38419;29.71383;-2.48120;,
 -8.62911;36.54383;-3.35802;,
 -8.62911;29.71383;-3.35802;,
 -8.38419;36.54383;-4.23483;,
 -8.38419;29.71383;-4.23483;,
 -7.79292;36.54383;-4.59802;,
 -7.79292;29.71383;-4.59802;,
 -7.79292;36.54383;-3.35802;,
 -7.79292;36.54383;-3.35802;,
 -7.79292;36.54383;-3.35802;,
 -7.79292;36.54383;-3.35802;,
 -7.79292;36.54383;-3.35802;,
 -7.79292;36.54383;-3.35802;,
 -7.79292;36.54383;-3.35802;,
 -7.79292;36.54383;-3.35802;,
 -7.79292;29.71383;-3.35802;,
 -7.79292;29.71383;-3.35802;,
 -7.79292;29.71383;-3.35802;,
 -7.79292;29.71383;-3.35802;,
 -7.79292;29.71383;-3.35802;,
 -7.79292;29.71383;-3.35802;,
 -7.79292;29.71383;-3.35802;,
 -7.79292;29.71383;-3.35802;,
 -7.33962;35.90602;-5.05551;,
 -7.33962;35.31476;-4.69232;,
 -14.16962;35.31476;-4.69232;,
 -14.16962;35.90602;-5.05551;,
 -7.33962;35.06984;-3.81551;,
 -14.16962;35.06984;-3.81551;,
 -7.33962;35.31476;-2.93870;,
 -14.16962;35.31476;-2.93870;,
 -7.33962;35.90602;-2.57551;,
 -14.16962;35.90602;-2.57551;,
 -7.33962;36.49730;-2.93870;,
 -14.16962;36.49730;-2.93870;,
 -7.33962;36.74221;-3.81551;,
 -14.16962;36.74221;-3.81551;,
 -7.33962;36.49730;-4.69232;,
 -14.16962;36.49730;-4.69232;,
 -7.33962;35.90602;-5.05551;,
 -14.16962;35.90602;-5.05551;,
 -7.33962;35.90602;-3.81551;,
 -7.33962;35.90602;-3.81551;,
 -7.33962;35.90602;-3.81551;,
 -7.33962;35.90602;-3.81551;,
 -7.33962;35.90602;-3.81551;,
 -7.33962;35.90602;-3.81551;,
 -7.33962;35.90602;-3.81551;,
 -7.33962;35.90602;-3.81551;,
 -14.16962;35.90602;-3.81551;,
 -14.16962;35.90602;-3.81551;,
 -14.16962;35.90602;-3.81551;,
 -14.16962;35.90602;-3.81551;,
 -14.16962;35.90602;-3.81551;,
 -14.16962;35.90602;-3.81551;,
 -14.16962;35.90602;-3.81551;,
 -14.16962;35.90602;-3.81551;,
 -7.33962;30.39251;-5.05551;,
 -7.33962;29.80123;-4.69232;,
 -14.16962;29.80123;-4.69232;,
 -14.16962;30.39251;-5.05551;,
 -7.33962;29.55632;-3.81551;,
 -14.16962;29.55632;-3.81551;,
 -7.33962;29.80123;-2.93870;,
 -14.16962;29.80123;-2.93870;,
 -7.33962;30.39251;-2.57551;,
 -14.16962;30.39251;-2.57551;,
 -7.33962;30.98378;-2.93870;,
 -14.16962;30.98378;-2.93870;,
 -7.33962;31.22869;-3.81551;,
 -14.16962;31.22869;-3.81551;,
 -7.33962;30.98378;-4.69232;,
 -14.16962;30.98378;-4.69232;,
 -7.33962;30.39251;-5.05551;,
 -14.16962;30.39251;-5.05551;,
 -7.33962;30.39251;-3.81551;,
 -7.33962;30.39251;-3.81551;,
 -7.33962;30.39251;-3.81551;,
 -7.33962;30.39251;-3.81551;,
 -7.33962;30.39251;-3.81551;,
 -7.33962;30.39251;-3.81551;,
 -7.33962;30.39251;-3.81551;,
 -7.33962;30.39251;-3.81551;,
 -14.16962;30.39251;-3.81551;,
 -14.16962;30.39251;-3.81551;,
 -14.16962;30.39251;-3.81551;,
 -14.16962;30.39251;-3.81551;,
 -14.16962;30.39251;-3.81551;,
 -14.16962;30.39251;-3.81551;,
 -14.16962;30.39251;-3.81551;,
 -14.16962;30.39251;-3.81551;,
 -5.83746;35.72963;-4.31947;,
 -6.10963;35.50924;-4.03074;,
 -7.51598;37.24594;-4.03074;,
 -7.24381;37.46635;-4.31947;,
 -6.22237;35.41794;-3.33369;,
 -7.62872;37.15464;-3.33369;,
 -6.10963;35.50924;-2.63663;,
 -7.51598;37.24594;-2.63663;,
 -5.83746;35.72963;-2.34790;,
 -7.24381;37.46635;-2.34790;,
 -5.56529;35.95004;-2.63663;,
 -6.97163;37.68674;-2.63663;,
 -5.45255;36.04134;-3.33369;,
 -6.85890;37.77804;-3.33369;,
 -5.56529;35.95004;-4.03074;,
 -6.97163;37.68674;-4.03074;,
 -5.83746;35.72963;-4.31947;,
 -7.24381;37.46635;-4.31947;,
 -5.83746;35.72963;-3.33369;,
 -5.83746;35.72963;-3.33369;,
 -5.83746;35.72963;-3.33369;,
 -5.83746;35.72963;-3.33369;,
 -5.83746;35.72963;-3.33369;,
 -5.83746;35.72963;-3.33369;,
 -5.83746;35.72963;-3.33369;,
 -5.83746;35.72963;-3.33369;,
 -7.24381;37.46635;-3.33369;,
 -7.24381;37.46635;-3.33369;,
 -7.24381;37.46635;-3.33369;,
 -7.24381;37.46635;-3.33369;,
 -7.24381;37.46635;-3.33369;,
 -7.24381;37.46635;-3.33369;,
 -7.24381;37.46635;-3.33369;,
 -7.24381;37.46635;-3.33369;,
 -4.67754;36.22889;-4.31947;,
 -4.94972;36.00850;-4.03074;,
 -6.35607;37.74521;-4.03074;,
 -6.08389;37.96560;-4.31947;,
 -5.06246;35.91720;-3.33369;,
 -6.46881;37.65390;-3.33369;,
 -4.94972;36.00850;-2.63663;,
 -6.35607;37.74521;-2.63663;,
 -4.67754;36.22889;-2.34790;,
 -6.08389;37.96560;-2.34790;,
 -4.40537;36.44929;-2.63663;,
 -5.81172;38.18600;-2.63663;,
 -4.29263;36.54060;-3.33369;,
 -5.69898;38.27730;-3.33369;,
 -4.40537;36.44929;-4.03074;,
 -5.81172;38.18600;-4.03074;,
 -4.67754;36.22889;-4.31947;,
 -6.08389;37.96560;-4.31947;,
 -4.67754;36.22889;-3.33369;,
 -4.67754;36.22889;-3.33369;,
 -4.67754;36.22889;-3.33369;,
 -4.67754;36.22889;-3.33369;,
 -4.67754;36.22889;-3.33369;,
 -4.67754;36.22889;-3.33369;,
 -4.67754;36.22889;-3.33369;,
 -4.67754;36.22889;-3.33369;,
 -6.08389;37.96560;-3.33369;,
 -6.08389;37.96560;-3.33369;,
 -6.08389;37.96560;-3.33369;,
 -6.08389;37.96560;-3.33369;,
 -6.08389;37.96560;-3.33369;,
 -6.08389;37.96560;-3.33369;,
 -6.08389;37.96560;-3.33369;,
 -6.08389;37.96560;-3.33369;,
 3.48068;33.11646;-5.05551;,
 3.48068;32.52519;-4.69232;,
 -5.06788;32.52519;-4.69232;,
 -5.06788;33.11646;-5.05551;,
 3.48068;32.28028;-3.81551;,
 -5.06788;32.28028;-3.81551;,
 3.48068;32.52519;-2.93870;,
 -5.06788;32.52519;-2.93870;,
 3.48068;33.11646;-2.57551;,
 -5.06788;33.11646;-2.57551;,
 3.48068;33.70774;-2.93870;,
 -5.06788;33.70774;-2.93870;,
 3.48068;33.95265;-3.81551;,
 -5.06788;33.95266;-3.81551;,
 3.48068;33.70774;-4.69232;,
 -5.06788;33.70774;-4.69232;,
 3.48068;33.11646;-5.05551;,
 -5.06788;33.11646;-5.05551;,
 3.48068;33.11646;-3.81551;,
 3.48068;33.11646;-3.81551;,
 3.48068;33.11646;-3.81551;,
 3.48068;33.11646;-3.81551;,
 3.48068;33.11646;-3.81551;,
 3.48068;33.11646;-3.81551;,
 3.48068;33.11646;-3.81551;,
 3.48068;33.11646;-3.81551;,
 -5.06788;33.11646;-3.81551;,
 -5.06788;33.11646;-3.81551;,
 -5.06788;33.11646;-3.81551;,
 -5.06788;33.11646;-3.81551;,
 -5.06788;33.11646;-3.81551;,
 -5.06788;33.11646;-3.81551;,
 -5.06788;33.11646;-3.81551;,
 -5.06788;33.11646;-3.81551;,
 11.81917;36.54689;-4.59802;,
 12.41044;36.54689;-4.23483;,
 12.41044;29.71689;-4.23483;,
 11.81917;29.71689;-4.59802;,
 12.65535;36.54689;-3.35802;,
 12.65535;29.71689;-3.35802;,
 12.41044;36.54689;-2.48120;,
 12.41044;29.71689;-2.48120;,
 11.81917;36.54689;-2.11802;,
 11.81917;29.71689;-2.11802;,
 11.22789;36.54689;-2.48120;,
 11.22789;29.71689;-2.48120;,
 10.98298;36.54689;-3.35802;,
 10.98298;29.71689;-3.35802;,
 11.22789;36.54689;-4.23483;,
 11.22789;29.71689;-4.23483;,
 11.81917;36.54689;-4.59802;,
 11.81917;29.71689;-4.59802;,
 11.81917;36.54689;-3.35802;,
 11.81917;36.54689;-3.35802;,
 11.81917;36.54689;-3.35802;,
 11.81917;36.54689;-3.35802;,
 11.81917;36.54689;-3.35802;,
 11.81917;36.54689;-3.35802;,
 11.81917;36.54689;-3.35802;,
 11.81917;36.54689;-3.35802;,
 11.81917;29.71689;-3.35802;,
 11.81917;29.71689;-3.35802;,
 11.81917;29.71689;-3.35802;,
 11.81917;29.71689;-3.35802;,
 11.81917;29.71689;-3.35802;,
 11.81917;29.71689;-3.35802;,
 11.81917;29.71689;-3.35802;,
 11.81917;29.71689;-3.35802;,
 14.62621;31.09244;-4.59802;,
 14.81382;30.53172;-4.23483;,
 11.79407;29.52134;-4.23483;,
 11.60646;30.08203;-4.59802;,
 14.89153;30.29945;-3.35802;,
 11.87178;29.28908;-3.35802;,
 14.81382;30.53172;-2.48120;,
 11.79407;29.52134;-2.48120;,
 14.62621;31.09244;-2.11802;,
 11.60646;30.08203;-2.11802;,
 14.43860;31.65314;-2.48120;,
 11.41885;30.64276;-2.48120;,
 14.36089;31.88540;-3.35802;,
 11.34113;30.87502;-3.35802;,
 14.43860;31.65314;-4.23483;,
 11.41885;30.64276;-4.23483;,
 14.62621;31.09244;-4.59802;,
 11.60646;30.08203;-4.59802;,
 14.62621;31.09244;-3.35802;,
 14.62621;31.09244;-3.35802;,
 14.62621;31.09244;-3.35802;,
 14.62621;31.09244;-3.35802;,
 14.62621;31.09244;-3.35802;,
 14.62621;31.09244;-3.35802;,
 14.62621;31.09244;-3.35802;,
 14.62621;31.09244;-3.35802;,
 11.60646;30.08203;-3.35802;,
 11.60646;30.08203;-3.35802;,
 11.60646;30.08203;-3.35802;,
 11.60646;30.08203;-3.35802;,
 11.60646;30.08203;-3.35802;,
 11.60646;30.08203;-3.35802;,
 11.60646;30.08203;-3.35802;,
 11.60646;30.08203;-3.35802;,
 8.33283;36.63196;-4.59802;,
 8.92410;36.63196;-4.23483;,
 8.92410;33.83494;-4.23483;,
 8.33283;33.83494;-4.59802;,
 9.16901;36.63196;-3.35802;,
 9.16901;33.83494;-3.35802;,
 8.92410;36.63196;-2.48120;,
 8.92410;33.83494;-2.48120;,
 8.33283;36.63196;-2.11802;,
 8.33283;33.83494;-2.11802;,
 7.74155;36.63196;-2.48120;,
 7.74155;33.83494;-2.48120;,
 7.49664;36.63196;-3.35802;,
 7.49664;33.83494;-3.35802;,
 7.74155;36.63196;-4.23483;,
 7.74155;33.83494;-4.23483;,
 8.33283;36.63196;-4.59802;,
 8.33283;33.83494;-4.59802;,
 8.33283;36.63196;-3.35802;,
 8.33283;36.63196;-3.35802;,
 8.33283;36.63196;-3.35802;,
 8.33283;36.63196;-3.35802;,
 8.33283;36.63196;-3.35802;,
 8.33283;36.63196;-3.35802;,
 8.33283;36.63196;-3.35802;,
 8.33283;36.63196;-3.35802;,
 8.57412;32.66282;-4.23483;,
 8.00720;32.83075;-4.59802;,
 8.80895;32.59326;-3.35802;,
 8.57412;32.66282;-2.48120;,
 8.00720;32.83075;-2.11802;,
 7.44028;32.99868;-2.48120;,
 7.20545;33.06824;-3.35802;,
 7.44028;32.99868;-4.23483;,
 8.00720;32.83075;-4.59802;,
 7.96263;31.22565;-4.23483;,
 7.45058;31.52129;-4.59802;,
 8.17473;31.10320;-3.35802;,
 7.96263;31.22565;-2.48120;,
 7.45058;31.52129;-2.11802;,
 6.93852;31.81693;-2.48120;,
 6.72642;31.93938;-3.35802;,
 6.93852;31.81693;-4.23483;,
 7.45058;31.52129;-4.59802;,
 6.58675;29.63232;-4.23483;,
 6.21867;30.09506;-4.59802;,
 6.21867;30.09506;-3.35802;,
 6.73921;29.44065;-3.35802;,
 6.21867;30.09506;-3.35802;,
 6.58675;29.63232;-2.48120;,
 6.21867;30.09506;-3.35802;,
 6.21867;30.09506;-2.11802;,
 6.21867;30.09506;-3.35802;,
 5.85060;30.55779;-2.48120;,
 6.21867;30.09506;-3.35802;,
 5.69813;30.74946;-3.35802;,
 6.21867;30.09506;-3.35802;,
 5.85060;30.55779;-4.23483;,
 6.21867;30.09506;-3.35802;,
 6.21867;30.09506;-4.59802;,
 6.21867;30.09506;-3.35802;;
 
 246;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;21,24,25,22;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 3;38,21,20;,
 3;39,24,21;,
 3;40,26,24;,
 3;41,28,26;,
 3;42,30,28;,
 3;43,32,30;,
 3;44,34,32;,
 3;45,36,34;,
 3;46,23,22;,
 3;47,22,25;,
 3;48,25,27;,
 3;49,27,29;,
 3;50,29,31;,
 3;51,31,33;,
 3;52,33,35;,
 3;53,35,37;,
 4;54,55,56,57;,
 4;55,58,59,56;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 4;64,66,67,65;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 3;72,55,54;,
 3;73,58,55;,
 3;74,60,58;,
 3;75,62,60;,
 3;76,64,62;,
 3;77,66,64;,
 3;78,68,66;,
 3;79,70,68;,
 3;80,57,56;,
 3;81,56,59;,
 3;82,59,61;,
 3;83,61,63;,
 3;84,63,65;,
 3;85,65,67;,
 3;86,67,69;,
 3;87,69,71;,
 4;88,89,90,91;,
 4;89,92,93,90;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 3;106,89,88;,
 3;107,92,89;,
 3;108,94,92;,
 3;109,96,94;,
 3;110,98,96;,
 3;111,100,98;,
 3;112,102,100;,
 3;113,104,102;,
 3;114,91,90;,
 3;115,90,93;,
 3;116,93,95;,
 3;117,95,97;,
 3;118,97,99;,
 3;119,99,101;,
 3;120,101,103;,
 3;121,103,105;,
 4;122,123,124,125;,
 4;123,126,127,124;,
 4;126,128,129,127;,
 4;128,130,131,129;,
 4;130,132,133,131;,
 4;132,134,135,133;,
 4;134,136,137,135;,
 4;136,138,139,137;,
 3;140,123,122;,
 3;141,126,123;,
 3;142,128,126;,
 3;143,130,128;,
 3;144,132,130;,
 3;145,134,132;,
 3;146,136,134;,
 3;147,138,136;,
 3;148,125,124;,
 3;149,124,127;,
 3;150,127,129;,
 3;151,129,131;,
 3;152,131,133;,
 3;153,133,135;,
 3;154,135,137;,
 3;155,137,139;,
 4;156,157,158,159;,
 4;157,160,161,158;,
 4;160,162,163,161;,
 4;162,164,165,163;,
 4;164,166,167,165;,
 4;166,168,169,167;,
 4;168,170,171,169;,
 4;170,172,173,171;,
 3;174,157,156;,
 3;175,160,157;,
 3;176,162,160;,
 3;177,164,162;,
 3;178,166,164;,
 3;179,168,166;,
 3;180,170,168;,
 3;181,172,170;,
 3;182,159,158;,
 3;183,158,161;,
 3;184,161,163;,
 3;185,163,165;,
 3;186,165,167;,
 3;187,167,169;,
 3;188,169,171;,
 3;189,171,173;,
 4;190,191,192,193;,
 4;191,194,195,192;,
 4;194,196,197,195;,
 4;196,198,199,197;,
 4;198,200,201,199;,
 4;200,202,203,201;,
 4;202,204,205,203;,
 4;204,206,207,205;,
 3;208,191,190;,
 3;209,194,191;,
 3;210,196,194;,
 3;211,198,196;,
 3;212,200,198;,
 3;213,202,200;,
 3;214,204,202;,
 3;215,206,204;,
 3;216,193,192;,
 3;217,192,195;,
 3;218,195,197;,
 3;219,197,199;,
 3;220,199,201;,
 3;221,201,203;,
 3;222,203,205;,
 3;223,205,207;,
 4;224,225,226,227;,
 4;225,228,229,226;,
 4;228,230,231,229;,
 4;230,232,233,231;,
 4;232,234,235,233;,
 4;234,236,237,235;,
 4;236,238,239,237;,
 4;238,240,241,239;,
 3;242,225,224;,
 3;243,228,225;,
 3;244,230,228;,
 3;245,232,230;,
 3;246,234,232;,
 3;247,236,234;,
 3;248,238,236;,
 3;249,240,238;,
 3;250,227,226;,
 3;251,226,229;,
 3;252,229,231;,
 3;253,231,233;,
 3;254,233,235;,
 3;255,235,237;,
 3;256,237,239;,
 3;257,239,241;,
 4;258,259,260,261;,
 4;259,262,263,260;,
 4;262,264,265,263;,
 4;264,266,267,265;,
 4;266,268,269,267;,
 4;268,270,271,269;,
 4;270,272,273,271;,
 4;272,274,275,273;,
 3;276,259,258;,
 3;277,262,259;,
 3;278,264,262;,
 3;279,266,264;,
 3;280,268,266;,
 3;281,270,268;,
 3;282,272,270;,
 3;283,274,272;,
 3;284,261,260;,
 3;285,260,263;,
 3;286,263,265;,
 3;287,265,267;,
 3;288,267,269;,
 3;289,269,271;,
 3;290,271,273;,
 3;291,273,275;,
 4;292,293,294,295;,
 4;293,296,297,294;,
 4;296,298,299,297;,
 4;298,300,301,299;,
 4;300,302,303,301;,
 4;302,304,305,303;,
 4;304,306,307,305;,
 4;306,308,309,307;,
 3;310,293,292;,
 3;311,296,293;,
 3;312,298,296;,
 3;313,300,298;,
 3;314,302,300;,
 3;315,304,302;,
 3;316,306,304;,
 3;317,308,306;,
 4;318,319,295,294;,
 4;320,318,294,297;,
 4;321,320,297,299;,
 4;322,321,299,301;,
 4;323,322,301,303;,
 4;324,323,303,305;,
 4;325,324,305,307;,
 4;326,325,307,309;,
 4;327,328,319,318;,
 4;329,327,318,320;,
 4;330,329,320,321;,
 4;331,330,321,322;,
 4;332,331,322,323;,
 4;333,332,323,324;,
 4;334,333,324,325;,
 4;335,334,325,326;,
 4;336,337,328,327;,
 3;338,337,336;,
 4;339,336,327,329;,
 3;340,336,339;,
 4;341,339,329,330;,
 3;342,339,341;,
 4;343,341,330,331;,
 3;344,341,343;,
 4;345,343,331,332;,
 3;346,343,345;,
 4;347,345,332,333;,
 3;348,345,347;,
 4;349,347,333,334;,
 3;350,347,349;,
 4;351,349,334,335;,
 3;352,349,351;;
 
 MeshMaterialList {
  2;
  246;
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.759216;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.570980;0.570980;0.570980;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  206;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.523395;0.000000;-0.852091;,
  0.798394;0.000000;-0.602136;,
  1.000000;0.000000;0.000000;,
  0.798394;0.000000;0.602136;,
  0.523395;0.000000;0.852091;,
  -0.798394;0.000000;0.602136;,
  -1.000000;0.000000;0.000000;,
  -0.798394;0.000000;-0.602136;,
  0.000000;-1.000000;-0.000000;,
  -0.523394;0.000000;0.852091;,
  -0.523394;0.000000;-0.852091;,
  1.000000;0.000000;0.000000;,
  0.000000;-0.523396;-0.852089;,
  0.000000;-0.798394;-0.602136;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.798394;0.602136;,
  0.000000;-0.523396;0.852089;,
  0.000000;0.798393;0.602136;,
  0.000000;1.000000;0.000000;,
  0.000000;0.798393;-0.602136;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.523393;0.852091;,
  0.000000;0.523393;-0.852091;,
  1.000000;0.000000;0.000000;,
  0.000000;-0.523395;-0.852091;,
  -0.000000;-0.798394;-0.602136;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;-0.798394;0.602136;,
  0.000000;-0.523395;0.852091;,
  0.000000;0.798394;0.602135;,
  0.000000;1.000000;0.000000;,
  0.000000;0.798394;-0.602135;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.523394;0.852091;,
  0.000000;0.523394;-0.852091;,
  0.629319;-0.777147;-0.000000;,
  -0.494360;-0.400321;-0.771590;,
  -0.665258;-0.538713;-0.516934;,
  -0.777147;-0.629319;-0.000000;,
  -0.665258;-0.538712;0.516934;,
  -0.494359;-0.400320;0.771591;,
  0.665259;0.538713;0.516933;,
  0.777147;0.629319;-0.000000;,
  0.665259;0.538713;-0.516932;,
  -0.629318;0.777148;-0.000000;,
  0.494360;0.400321;0.771590;,
  0.494361;0.400322;-0.771589;,
  0.629307;-0.777157;-0.000003;,
  0.629315;-0.777150;-0.000000;,
  0.629311;-0.777153;-0.000000;,
  0.629307;-0.777157;0.000003;,
  0.629315;-0.777150;-0.000000;,
  0.629331;-0.777138;-0.000002;,
  0.629334;-0.777135;0.000000;,
  0.629331;-0.777138;0.000002;,
  -0.629315;0.777151;0.000000;,
  -0.629329;0.777139;0.000001;,
  -0.629331;0.777138;0.000000;,
  -0.629329;0.777139;-0.000001;,
  -0.629315;0.777151;0.000000;,
  -0.629308;0.777156;0.000004;,
  -0.629314;0.777151;-0.000000;,
  -0.629308;0.777156;-0.000004;,
  0.629315;-0.777151;-0.000000;,
  -0.494360;-0.400322;-0.771589;,
  -0.665257;-0.538712;-0.516935;,
  -0.777147;-0.629319;-0.000000;,
  -0.665257;-0.538712;0.516936;,
  -0.494359;-0.400321;0.771590;,
  0.665258;0.538713;0.516933;,
  0.777147;0.629319;-0.000000;,
  0.665259;0.538713;-0.516932;,
  -0.629317;0.777148;-0.000000;,
  0.494361;0.400323;0.771588;,
  0.494362;0.400324;-0.771587;,
  0.629308;-0.777156;-0.000006;,
  0.629308;-0.777156;-0.000000;,
  0.629317;-0.777148;-0.000000;,
  0.629308;-0.777156;0.000006;,
  0.629322;-0.777145;-0.000003;,
  0.629326;-0.777141;0.000000;,
  0.629322;-0.777145;0.000003;,
  -0.629310;0.777154;0.000000;,
  -0.629324;0.777143;0.000004;,
  -0.629331;0.777138;0.000000;,
  -0.629324;0.777143;-0.000004;,
  -0.629311;0.777154;0.000005;,
  -0.629319;0.777147;-0.000000;,
  -0.629311;0.777154;-0.000005;,
  1.000000;0.000000;0.000000;,
  0.000000;-0.523395;-0.852090;,
  -0.000000;-0.798394;-0.602136;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;-0.798394;0.602136;,
  0.000000;-0.523395;0.852090;,
  0.000000;0.798393;0.602136;,
  0.000000;1.000000;0.000000;,
  0.000000;0.798393;-0.602136;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.523393;0.852091;,
  0.000000;0.523393;-0.852091;,
  0.000000;1.000000;0.000000;,
  0.523393;0.000000;-0.852091;,
  0.798394;0.000000;-0.602135;,
  1.000000;0.000000;0.000000;,
  0.798394;0.000000;0.602135;,
  0.523393;0.000000;0.852091;,
  -0.798394;0.000000;0.602135;,
  -1.000000;0.000000;0.000000;,
  -0.798394;0.000000;-0.602135;,
  0.000000;-1.000000;-0.000000;,
  -0.523395;0.000000;0.852090;,
  -0.523395;0.000000;-0.852090;,
  0.948325;0.317300;0.000000;,
  0.166078;-0.496352;-0.852088;,
  0.253332;-0.757136;-0.602135;,
  0.317301;-0.948325;-0.000000;,
  0.253332;-0.757136;0.602135;,
  0.166078;-0.496352;0.852088;,
  -0.253333;0.757136;0.602135;,
  -0.317301;0.948325;0.000000;,
  -0.253333;0.757136;-0.602135;,
  -0.948325;-0.317300;0.000000;,
  -0.166078;0.496352;0.852087;,
  -0.166078;0.496352;-0.852087;,
  0.948326;0.317297;-0.000002;,
  0.948325;0.317300;0.000000;,
  0.948325;0.317299;0.000000;,
  0.948326;0.317297;0.000002;,
  0.948324;0.317303;0.000001;,
  0.948325;0.317302;0.000000;,
  0.948324;0.317303;-0.000001;,
  -0.948326;-0.317299;0.000000;,
  -0.948325;-0.317301;-0.000000;,
  -0.948325;-0.317301;0.000000;,
  -0.948325;-0.317301;0.000000;,
  -0.948326;-0.317299;0.000002;,
  -0.948325;-0.317302;0.000000;,
  -0.948326;-0.317299;-0.000002;,
  0.000000;1.000000;0.000000;,
  0.523395;0.000000;-0.852090;,
  0.798394;0.000000;-0.602136;,
  1.000000;0.000000;0.000000;,
  0.798394;0.000000;0.602136;,
  0.523395;0.000000;0.852090;,
  -0.798394;0.000000;0.602135;,
  -1.000000;0.000000;0.000000;,
  -0.798394;0.000000;-0.602135;,
  0.517124;-0.079227;-0.852236;,
  0.789007;-0.116277;-0.603281;,
  0.989765;-0.142709;-0.000000;,
  0.789007;-0.116277;0.603281;,
  0.517124;-0.079227;0.852236;,
  -0.785045;0.137535;0.603977;,
  -0.984309;0.176451;0.000000;,
  -0.785045;0.137535;-0.603977;,
  0.496010;-0.181976;-0.849034;,
  0.753208;-0.272265;-0.598790;,
  0.941332;-0.337482;-0.000000;,
  0.753208;-0.272265;0.598790;,
  0.496010;-0.181976;0.849034;,
  -0.746683;0.292556;0.597391;,
  -0.929452;0.368944;0.000000;,
  -0.746683;0.292556;-0.597391;,
  0.444127;-0.277111;-0.852033;,
  0.676745;-0.421964;-0.603293;,
  0.848651;-0.528954;-0.000001;,
  0.676745;-0.421964;0.603292;,
  0.444127;-0.277111;0.852033;,
  -0.676821;0.421798;0.603324;,
  -0.848803;0.528710;0.000000;,
  -0.676821;0.421798;-0.603324;,
  0.401213;-0.346503;-0.847917;,
  0.607102;-0.524258;-0.597144;,
  0.756878;-0.653556;-0.000001;,
  0.607103;-0.524258;0.597143;,
  0.401214;-0.346503;0.847917;,
  -0.606959;0.524424;0.597144;,
  -0.756652;0.653818;0.000000;,
  -0.606959;0.524424;-0.597144;,
  -0.782608;-0.622514;-0.000000;,
  -0.523394;0.000000;0.852091;,
  -0.515926;0.086571;0.852248;,
  -0.523394;0.000000;-0.852091;,
  -0.515926;0.086571;-0.852248;,
  -0.494453;0.189123;0.848380;,
  -0.494453;0.189123;-0.848380;,
  -0.444146;0.277049;0.852044;,
  -0.444146;0.277049;-0.852044;,
  -0.782609;-0.622514;-0.000000;,
  -0.782608;-0.622515;0.000000;,
  -0.782607;-0.622516;-0.000000;,
  -0.782608;-0.622515;-0.000000;,
  -0.782609;-0.622514;0.000000;,
  -0.401163;0.346559;0.847918;,
  -0.782608;-0.622514;0.000001;,
  -0.782608;-0.622515;0.000000;,
  -0.782608;-0.622514;-0.000001;,
  -0.401163;0.346559;-0.847918;;
  246;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;16,12,12,16;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,17,17,14;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;28,24,24,28;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,29,29,26;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,34,34,33;,
  4;34,35,35,34;,
  4;40,36,36,40;,
  4;36,37,37,36;,
  4;37,38,38,37;,
  4;38,41,41,38;,
  3;30,30,30;,
  3;30,30,30;,
  3;30,30,30;,
  3;30,30,30;,
  3;30,30,30;,
  3;30,30,30;,
  3;30,30,30;,
  3;30,30,30;,
  3;39,39,39;,
  3;39,39,39;,
  3;39,39,39;,
  3;39,39,39;,
  3;39,39,39;,
  3;39,39,39;,
  3;39,39,39;,
  3;39,39,39;,
  4;43,44,44,43;,
  4;44,45,45,44;,
  4;45,46,46,45;,
  4;46,47,47,46;,
  4;52,48,48,52;,
  4;48,49,49,48;,
  4;49,50,50,49;,
  4;50,53,53,50;,
  3;42,54,55;,
  3;42,56,54;,
  3;42,57,56;,
  3;42,58,57;,
  3;42,59,58;,
  3;42,60,59;,
  3;42,61,60;,
  3;42,55,61;,
  3;51,62,63;,
  3;51,63,64;,
  3;51,64,65;,
  3;51,65,66;,
  3;51,66,67;,
  3;51,67,68;,
  3;51,68,69;,
  3;51,69,62;,
  4;71,72,72,71;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;80,76,76,80;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,81,81,78;,
  3;70,82,83;,
  3;70,84,82;,
  3;70,85,84;,
  3;70,83,85;,
  3;70,86,83;,
  3;70,87,86;,
  3;70,88,87;,
  3;70,83,88;,
  3;79,89,90;,
  3;79,90,91;,
  3;79,91,92;,
  3;79,92,89;,
  3;79,89,93;,
  3;79,93,94;,
  3;79,94,95;,
  3;79,95,89;,
  4;97,98,98,97;,
  4;98,99,99,98;,
  4;99,100,100,99;,
  4;100,101,101,100;,
  4;106,102,102,106;,
  4;102,103,103,102;,
  4;103,104,104,103;,
  4;104,107,107,104;,
  3;96,96,96;,
  3;96,96,96;,
  3;96,96,96;,
  3;96,96,96;,
  3;96,96,96;,
  3;96,96,96;,
  3;96,96,96;,
  3;96,96,96;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  4;109,110,110,109;,
  4;110,111,111,110;,
  4;111,112,112,111;,
  4;112,113,113,112;,
  4;118,114,114,118;,
  4;114,115,115,114;,
  4;115,116,116,115;,
  4;116,119,119,116;,
  3;108,108,108;,
  3;108,108,108;,
  3;108,108,108;,
  3;108,108,108;,
  3;108,108,108;,
  3;108,108,108;,
  3;108,108,108;,
  3;108,108,108;,
  3;117,117,117;,
  3;117,117,117;,
  3;117,117,117;,
  3;117,117,117;,
  3;117,117,117;,
  3;117,117,117;,
  3;117,117,117;,
  3;117,117,117;,
  4;121,122,122,121;,
  4;122,123,123,122;,
  4;123,124,124,123;,
  4;124,125,125,124;,
  4;130,126,126,130;,
  4;126,127,127,126;,
  4;127,128,128,127;,
  4;128,131,131,128;,
  3;120,132,133;,
  3;120,134,132;,
  3;120,135,134;,
  3;120,133,135;,
  3;120,136,133;,
  3;120,137,136;,
  3;120,138,137;,
  3;120,133,138;,
  3;129,139,140;,
  3;129,140,141;,
  3;129,141,142;,
  3;129,142,139;,
  3;129,139,143;,
  3;129,143,144;,
  3;129,144,145;,
  3;129,145,139;,
  4;147,148,156,155;,
  4;148,149,157,156;,
  4;149,150,158,157;,
  4;150,151,159,158;,
  4;188,152,160,189;,
  4;152,153,161,160;,
  4;153,154,162,161;,
  4;154,190,191,162;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  4;164,163,155,156;,
  4;165,164,156,157;,
  4;166,165,157,158;,
  4;167,166,158,159;,
  4;168,192,189,160;,
  4;169,168,160,161;,
  4;170,169,161,162;,
  4;193,170,162,191;,
  4;172,171,163,164;,
  4;173,172,164,165;,
  4;174,173,165,166;,
  4;175,174,166,167;,
  4;176,194,192,168;,
  4;177,176,168,169;,
  4;178,177,169,170;,
  4;195,178,170,193;,
  4;180,179,171,172;,
  3;187,196,197;,
  4;181,180,172,173;,
  3;187,197,198;,
  4;182,181,173,174;,
  3;187,198,199;,
  4;183,182,174,175;,
  3;187,199,200;,
  4;184,201,194,176;,
  3;187,200,202;,
  4;185,184,176,177;,
  3;187,202,203;,
  4;186,185,177,178;,
  3;187,203,204;,
  4;205,186,178,195;,
  3;187,204,196;;
 }
 MeshTextureCoords {
  353;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.062500;1.000000;,
  0.250000;1.000000;,
  0.187500;1.000000;,
  0.375000;1.000000;,
  0.312500;1.000000;,
  0.500000;1.000000;,
  0.437500;1.000000;,
  0.625000;1.000000;,
  0.562500;1.000000;,
  0.750000;1.000000;,
  0.687500;1.000000;,
  0.875000;1.000000;,
  0.812500;1.000000;,
  1.000000;1.000000;,
  0.937500;1.000000;;
 }
}
