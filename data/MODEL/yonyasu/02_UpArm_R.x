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
 140;
 0.68875;-4.50198;1.62134;,
 0.55429;-5.10468;1.79981;,
 0.53329;-4.95335;0.44560;,
 -0.83323;-4.28089;2.12982;,
 -1.29676;-4.68375;1.27432;,
 -0.95249;-4.86802;2.29798;,
 0.07848;-4.20399;2.20236;,
 -0.05979;-5.22371;2.29820;,
 0.55429;-5.10468;1.79981;,
 0.68875;-4.50198;1.62134;,
 -0.95249;-4.86802;2.29798;,
 -0.05979;-5.22371;2.29820;,
 0.07848;-4.20399;2.20236;,
 1.08775;-3.34854;1.12065;,
 0.68875;-4.50198;1.62134;,
 0.94030;-3.45632;-0.27889;,
 0.22676;-3.45268;-1.32662;,
 0.01744;-5.00312;-0.21864;,
 -0.69531;-4.95239;-0.22918;,
 -0.88098;-3.39286;-1.02763;,
 0.94030;-3.45632;-0.27889;,
 0.53329;-4.95335;0.44560;,
 0.01744;-5.00312;-0.21864;,
 0.22676;-3.45268;-1.32662;,
 0.36447;-3.10362;2.23743;,
 0.07848;-4.20399;2.20236;,
 0.68875;-4.50198;1.62134;,
 1.08775;-3.34854;1.12065;,
 -0.88098;-3.39286;-1.02763;,
 -0.69531;-4.95239;-0.22918;,
 -1.34791;-4.78804;0.32302;,
 -1.90785;-3.15686;0.33276;,
 -1.90785;-3.15686;0.33276;,
 -1.34791;-4.78804;0.32302;,
 -1.29676;-4.68375;1.27432;,
 -1.77901;-3.01217;1.71641;,
 -0.58973;-2.95894;2.49049;,
 -0.83323;-4.28089;2.12982;,
 0.07848;-4.20399;2.20236;,
 0.36447;-3.10362;2.23743;,
 -1.77901;-3.01217;1.71641;,
 -0.83323;-4.28089;2.12982;,
 -0.58973;-2.95894;2.49049;,
 0.68130;0.64554;2.17167;,
 -0.72599;1.91469;1.60547;,
 -1.31656;1.13496;1.51174;,
 0.08687;-0.19010;2.14954;,
 1.28564;-0.53037;1.60547;,
 0.68130;0.64554;2.17167;,
 0.08687;-0.19010;2.14954;,
 1.06137;-1.00275;1.64234;,
 -0.72599;1.91469;1.60547;,
 -1.09029;2.29635;0.23857;,
 -1.62361;0.96452;0.09416;,
 -1.31656;1.13496;1.51174;,
 -1.09029;2.29635;0.23857;,
 -0.72599;1.91469;-1.12834;,
 -0.94052;0.73490;-1.22463;,
 -1.62361;0.96452;0.09416;,
 1.64661;-1.15089;0.23857;,
 1.28564;-0.53037;1.60547;,
 1.06137;-1.00275;1.64234;,
 1.45024;-1.32027;0.09416;,
 0.68130;0.64554;-1.69453;,
 1.28564;-0.53037;-1.12834;,
 1.15527;-0.94420;-1.13031;,
 0.43237;-0.30643;-1.73184;,
 -0.72599;1.91469;-1.12834;,
 0.68130;0.64554;-1.69453;,
 0.43237;-0.30643;-1.73184;,
 -0.94052;0.73490;-1.22463;,
 1.28564;-0.53037;-1.12834;,
 1.64661;-1.15089;0.23857;,
 1.45024;-1.32027;0.09416;,
 1.15527;-0.94420;-1.13031;,
 1.45024;-1.32027;0.09416;,
 1.50769;-1.93302;0.78432;,
 1.29976;-1.98275;-0.61701;,
 1.50769;-1.93302;0.78432;,
 1.08775;-3.34854;1.12065;,
 0.94030;-3.45632;-0.27889;,
 1.29976;-1.98275;-0.61701;,
 0.43237;-0.30643;-1.73184;,
 0.42054;-1.66892;-1.64297;,
 -0.92317;-1.13123;-1.30378;,
 0.42054;-1.66892;-1.64297;,
 0.22676;-3.45268;-1.32662;,
 -0.88098;-3.39286;-1.02763;,
 -0.92317;-1.13123;-1.30378;,
 1.15527;-0.94420;-1.13031;,
 1.29976;-1.98275;-0.61701;,
 0.42054;-1.66892;-1.64297;,
 1.29976;-1.98275;-0.61701;,
 0.94030;-3.45632;-0.27889;,
 0.22676;-3.45268;-1.32662;,
 0.42054;-1.66892;-1.64297;,
 1.06137;-1.00275;1.64234;,
 0.66694;-1.35396;1.93407;,
 1.50769;-1.93302;0.78432;,
 0.66694;-1.35396;1.93407;,
 0.36447;-3.10362;2.23743;,
 1.08775;-3.34854;1.12065;,
 1.50769;-1.93302;0.78432;,
 -0.94052;0.73490;-1.22463;,
 -0.92317;-1.13123;-1.30378;,
 -2.01579;-0.65427;0.08200;,
 -0.92317;-1.13123;-1.30378;,
 -0.88098;-3.39286;-1.02763;,
 -1.90785;-3.15686;0.33276;,
 -2.01579;-0.65427;0.08200;,
 -1.62361;0.96452;0.09416;,
 -2.01579;-0.65427;0.08200;,
 -1.82574;-0.55443;1.46864;,
 -2.01579;-0.65427;0.08200;,
 -1.90785;-3.15686;0.33276;,
 -1.77901;-3.01217;1.71641;,
 -1.82574;-0.55443;1.46864;,
 0.08687;-0.19010;2.14954;,
 -0.47785;-0.78448;2.22326;,
 0.66694;-1.35396;1.93407;,
 -0.47785;-0.78448;2.22326;,
 -0.58973;-2.95894;2.49049;,
 0.36447;-3.10362;2.23743;,
 0.66694;-1.35396;1.93407;,
 -1.31656;1.13496;1.51174;,
 -1.82574;-0.55443;1.46864;,
 -0.47785;-0.78448;2.22326;,
 -1.82574;-0.55443;1.46864;,
 -1.77901;-3.01217;1.71641;,
 -0.58973;-2.95894;2.49049;,
 -0.47785;-0.78448;2.22326;,
 -0.27212;-5.35671;1.20846;,
 -0.05979;-5.22371;2.29820;,
 0.55429;-5.10468;1.79981;,
 0.53329;-4.95335;0.44560;,
 0.01744;-5.00312;-0.21864;,
 -0.69531;-4.95239;-0.22918;,
 -1.34791;-4.78804;0.32302;,
 -0.95249;-4.86802;2.29798;,
 -1.29676;-4.68375;1.27432;;
 
 44;
 3;0,1,2;,
 3;3,4,5;,
 4;6,7,8,9;,
 4;3,10,11,12;,
 4;13,14,2,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,4,41,42;,
 4;43,44,45,46;,
 4;47,48,49,50;,
 4;51,52,53,54;,
 4;55,56,57,58;,
 4;59,60,61,62;,
 4;63,64,65,66;,
 4;67,68,69,70;,
 4;71,72,73,74;,
 4;75,76,77,74;,
 4;78,79,80,81;,
 4;82,83,84,70;,
 4;85,86,87,88;,
 4;89,90,91,66;,
 4;92,93,94,95;,
 4;96,97,98,62;,
 4;99,100,101,102;,
 4;103,104,105,58;,
 4;106,107,108,109;,
 4;110,111,112,54;,
 4;113,114,115,116;,
 4;117,118,119,50;,
 4;120,121,122,123;,
 4;124,125,126,46;,
 4;127,128,129,130;,
 3;131,132,10;,
 3;131,133,7;,
 3;131,134,1;,
 3;131,135,21;,
 3;131,136,17;,
 3;131,137,29;,
 3;131,138,4;,
 3;131,139,33;;
 
 MeshMaterialList {
  10;
  44;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  2,
  4,
  2,
  4,
  2,
  4,
  2,
  4,
  2,
  4,
  2,
  4,
  2,
  4,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.512000;0.512000;0.512000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.160000;0.160000;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.690400;0.492800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.179200;0.100000;0.053600;1.000000;;
   14.000000;
   0.080000;0.080000;0.080000;;
   0.024640;0.013750;0.007370;;
  }
  Material {
   0.458400;0.800000;0.787200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.269600;0.140800;0.047200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.527200;0.125600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.050400;0.097600;1.000000;;
   20.000000;
   0.150000;0.150000;0.150000;;
   0.000000;0.011970;0.023180;;
  }
  Material {
   0.040800;0.040800;0.040800;1.000000;;
   15.000000;
   0.140000;0.140000;0.140000;;
   0.005100;0.005100;0.005100;;
  }
 }
 MeshNormals {
  50;
  -0.892912;0.281914;0.351045;,
  0.361798;0.108130;0.925964;,
  0.912918;-0.116066;0.391292;,
  -0.130718;-0.990707;-0.037577;,
  0.313246;-0.403810;-0.859543;,
  0.881061;-0.339754;-0.329087;,
  0.931254;-0.210692;0.297278;,
  -0.521763;-0.291902;-0.801596;,
  -0.941479;-0.207762;-0.265430;,
  0.516851;-0.067893;0.853379;,
  -0.218549;-0.059008;0.974040;,
  -0.858377;-0.132950;0.495493;,
  -0.834460;-0.456054;0.309341;,
  -0.721402;-0.676310;-0.148940;,
  -0.363441;-0.773795;-0.518798;,
  0.237771;-0.827108;-0.509271;,
  0.743223;-0.639932;-0.195208;,
  0.914563;-0.175820;0.364228;,
  0.408826;-0.025489;0.912256;,
  -0.822191;0.016369;0.568977;,
  0.035572;0.044479;0.998377;,
  0.645210;-0.215602;0.732953;,
  0.955148;-0.287907;0.069290;,
  0.804491;-0.188427;-0.563284;,
  0.181379;-0.050993;-0.982090;,
  -0.610878;0.138674;-0.779486;,
  -0.941978;0.299586;-0.151415;,
  -0.693956;0.300289;0.654409;,
  -0.645219;0.333529;0.687351;,
  -0.915513;0.394203;-0.080253;,
  -0.623181;0.223790;-0.749375;,
  0.153567;-0.012062;-0.988065;,
  0.726141;-0.282324;-0.626907;,
  0.832855;-0.553436;-0.007837;,
  0.575305;-0.439477;0.689844;,
  0.043341;-0.027425;0.998684;,
  -0.967924;0.071165;-0.240953;,
  0.882771;-0.186951;-0.431004;,
  -0.583088;-0.031232;-0.811808;,
  -0.048476;0.117064;0.991941;,
  0.629414;0.019732;0.776820;,
  0.247078;-0.160519;-0.955608;,
  0.975388;-0.095754;0.198620;,
  -0.904001;0.125785;0.408608;,
  0.051604;0.002680;0.998664;,
  0.006868;0.181263;0.983411;,
  -0.323768;0.201228;0.924490;,
  -0.062807;-0.989130;0.132959;,
  -0.459116;-0.881693;0.108769;,
  0.304378;-0.952352;-0.019481;;
  44;
  3;17,2,16;,
  3;19,12,0;,
  4;18,1,2,17;,
  4;44,45,1,18;,
  4;6,17,16,5;,
  4;4,15,14,7;,
  4;5,16,15,4;,
  4;9,18,17,6;,
  4;7,14,13,8;,
  4;8,13,12,11;,
  4;10,44,18,9;,
  4;11,12,19,10;,
  4;35,28,27,20;,
  4;34,35,20,21;,
  4;28,29,26,27;,
  4;29,30,25,26;,
  4;33,34,21,22;,
  4;31,32,23,24;,
  4;30,31,24,25;,
  4;32,33,22,23;,
  4;22,42,37,23;,
  4;42,6,5,37;,
  4;24,41,38,25;,
  4;41,4,7,38;,
  4;23,37,41,24;,
  4;37,5,4,41;,
  4;21,40,42,22;,
  4;40,9,6,42;,
  4;25,38,36,26;,
  4;38,7,8,36;,
  4;26,36,43,27;,
  4;36,8,11,43;,
  4;20,39,40,21;,
  4;39,10,9,40;,
  4;27,46,39,20;,
  4;43,11,10,39;,
  3;3,47,48;,
  3;3,49,47;,
  3;3,16,49;,
  3;3,15,16;,
  3;3,14,15;,
  3;3,13,14;,
  3;3,48,12;,
  3;3,12,13;;
 }
 MeshTextureCoords {
  140;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
