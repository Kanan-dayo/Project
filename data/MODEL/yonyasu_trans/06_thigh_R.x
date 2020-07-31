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
 116;
 0.66758;-6.52237;2.02510;,
 -0.63338;-6.26000;2.63061;,
 -0.59804;-9.90262;2.61516;,
 0.29359;-10.62845;2.28264;,
 1.20646;-6.83844;0.51543;,
 0.66758;-6.52237;2.02510;,
 0.29359;-10.62845;2.28264;,
 0.69877;-10.50420;1.10641;,
 0.66758;-7.02304;-1.01408;,
 1.20646;-6.83844;0.51543;,
 0.69877;-10.50420;1.10641;,
 0.27830;-10.38009;-0.12875;,
 -0.63338;-6.96802;-1.66747;,
 0.66758;-7.02304;-1.01408;,
 0.27830;-10.38009;-0.12875;,
 -0.67713;-10.23974;-0.57232;,
 -1.93435;-6.70566;-1.06195;,
 -0.63338;-6.96802;-1.66747;,
 -0.67713;-10.23974;-0.57232;,
 -1.62424;-10.07483;-0.11988;,
 -2.47323;-6.38959;0.44773;,
 -1.93435;-6.70566;-1.06195;,
 -1.62424;-10.07483;-0.11988;,
 -1.99181;-10.07248;1.11897;,
 -1.93435;-6.20500;1.97724;,
 -2.47323;-6.38959;0.44773;,
 -1.99181;-10.07248;1.11897;,
 -1.60894;-10.32316;2.29152;,
 -0.63338;-6.26000;2.63061;,
 -1.93435;-6.20500;1.97724;,
 -1.60894;-10.32316;2.29152;,
 -0.59804;-9.90262;2.61516;,
 1.03564;-0.83743;1.82907;,
 -0.11198;0.42896;2.73209;,
 -0.22282;-2.90819;2.52884;,
 1.00381;-3.06825;1.83187;,
 1.49751;-1.47358;0.13133;,
 1.03564;-0.83743;1.82907;,
 1.00381;-3.06825;1.83187;,
 1.47544;-3.66191;0.14582;,
 1.03564;-0.86062;-1.56642;,
 1.49751;-1.47358;0.13133;,
 1.47544;-3.66191;0.14582;,
 1.00381;-3.10092;-1.54163;,
 0.64064;-0.05311;-2.29188;,
 1.03564;-0.86062;-1.56642;,
 1.00381;-3.10092;-1.54163;,
 -0.22282;-2.95439;-2.24200;,
 -1.14588;1.27536;-1.64037;,
 0.64064;-0.05311;-2.29188;,
 -0.22282;-2.95439;-2.24200;,
 -1.80199;-2.50891;-1.54502;,
 -1.58114;1.48212;0.13133;,
 -1.14588;1.27536;-1.64037;,
 -1.80199;-2.50891;-1.54502;,
 -2.36432;-2.29195;0.14103;,
 -1.48371;1.01894;2.13027;,
 -1.58114;1.48212;0.13133;,
 -2.36432;-2.29195;0.14103;,
 -1.80199;-2.47625;1.82847;,
 -0.11198;0.42896;2.73209;,
 -1.48371;1.01894;2.13027;,
 -1.80199;-2.47625;1.82847;,
 -0.22282;-2.90819;2.52884;,
 -1.60894;-10.32316;2.29152;,
 -1.68279;-11.66929;2.38958;,
 -0.72661;-11.78990;2.83570;,
 -0.59804;-9.90262;2.61516;,
 -1.99181;-10.07248;1.11897;,
 -2.10350;-11.82685;1.29319;,
 -1.68279;-11.66929;2.38958;,
 -1.60894;-10.32316;2.29152;,
 -1.62424;-10.07483;-0.11988;,
 -1.73894;-11.57516;-0.04838;,
 -2.10350;-11.82685;1.29319;,
 -1.99181;-10.07248;1.11897;,
 -0.67713;-10.23974;-0.57232;,
 -0.78205;-11.57394;-0.53734;,
 -1.73894;-11.57516;-0.04838;,
 -1.62424;-10.07483;-0.11988;,
 0.27830;-10.38009;-0.12875;,
 0.15941;-11.84420;-0.04393;,
 -0.78205;-11.57394;-0.53734;,
 -0.67713;-10.23974;-0.57232;,
 0.69877;-10.50420;1.10641;,
 0.56607;-12.38585;1.31355;,
 0.15941;-11.84420;-0.04393;,
 0.27830;-10.38009;-0.12875;,
 0.29359;-10.62845;2.28264;,
 0.20490;-12.06455;2.40398;,
 0.56607;-12.38585;1.31355;,
 0.69877;-10.50420;1.10641;,
 -0.59804;-9.90262;2.61516;,
 -0.72661;-11.78990;2.83570;,
 0.20490;-12.06455;2.40398;,
 0.29359;-10.62845;2.28264;,
 -0.78205;-11.57394;-0.53734;,
 0.15941;-11.84420;-0.04393;,
 0.03244;-13.13640;0.36428;,
 -0.93843;-13.16545;-0.03457;,
 -1.73894;-11.57516;-0.04838;,
 -0.78205;-11.57394;-0.53734;,
 -0.93843;-13.16545;-0.03457;,
 -1.86060;-12.81332;0.34277;,
 -2.10350;-11.82685;1.29319;,
 -1.73894;-11.57516;-0.04838;,
 -1.86060;-12.81332;0.34277;,
 0.15941;-11.84420;-0.04393;,
 0.56607;-12.38585;1.31355;,
 -1.07344;-12.52048;1.67798;,
 -1.86060;-12.81332;0.34277;,
 -1.86060;-12.81332;0.34277;,
 -0.93843;-13.16545;-0.03457;,
 -0.93843;-13.16545;-0.03457;,
 0.03244;-13.13640;0.36428;,
 0.03244;-13.13640;0.36428;;
 
 47;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;35,34,1,0;,
 4;36,37,38,39;,
 4;39,38,5,4;,
 4;40,41,42,43;,
 4;43,42,9,8;,
 4;44,45,46,47;,
 4;47,46,13,12;,
 4;48,49,50,51;,
 4;51,50,17,16;,
 4;52,53,54,55;,
 4;55,54,21,20;,
 4;56,57,58,59;,
 4;59,58,25,24;,
 4;60,61,62,63;,
 4;63,62,29,28;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 3;104,105,106;,
 3;107,108,98;,
 3;109,66,65;,
 3;109,70,69;,
 3;109,74,110;,
 3;109,111,112;,
 3;109,113,114;,
 3;109,115,85;,
 3;109,90,89;,
 3;109,94,93;,
 4;37,36,40,44;,
 4;33,37,44,48;,
 4;48,57,61,33;;
 
 MeshMaterialList {
  19;
  47;
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
  2;;
  Material {
   0.800000;0.053600;0.000000;1.000000;;
   29.000000;
   0.310000;0.310000;0.310000;;
   0.230000;0.015410;0.000000;;
  }
  Material {
   0.800000;0.091200;0.615200;0.700000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.592800;0.470400;0.257600;1.000000;;
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
   0.222400;0.664800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.172800;0.624000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.636800;0.000000;1.000000;;
   24.000000;
   0.200000;0.200000;0.200000;;
   0.170000;0.135320;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.184800;0.078400;0.024800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.084800;0.780000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.213600;0.213600;0.213600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.062400;0.775200;0.800000;0.320000;;
   29.000000;
   0.250000;0.250000;0.250000;;
   0.016380;0.203490;0.210000;;
  }
  Material {
   0.552000;0.398400;0.078400;1.000000;;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.012800;0.012800;0.012800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.341600;0.448800;0.800000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.304000;0.235200;0.213600;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  54;
  0.066293;-0.044602;0.996803;,
  -0.776763;0.050815;0.627740;,
  -0.986454;0.158281;-0.043079;,
  -0.718118;0.133068;-0.683080;,
  0.621870;-0.124294;-0.773194;,
  0.909686;0.141584;-0.390417;,
  0.984623;0.174687;-0.001545;,
  0.876687;0.350238;0.329779;,
  0.736162;-0.006565;0.676773;,
  0.994786;-0.101942;0.002862;,
  0.732436;-0.174389;-0.658123;,
  -0.019836;-0.177296;-0.983958;,
  -0.767215;-0.110044;-0.631880;,
  -0.999348;-0.025520;0.025536;,
  -0.727590;0.043227;0.684649;,
  0.012013;0.056301;0.998342;,
  0.743430;-0.034518;0.667922;,
  0.012738;0.023621;0.999640;,
  0.993433;-0.114269;0.005729;,
  0.737214;-0.204199;-0.644064;,
  -0.008388;-0.227032;-0.973851;,
  -0.752400;-0.147110;-0.642070;,
  -0.998779;-0.048865;0.007312;,
  -0.737214;0.020917;0.675335;,
  0.779895;-0.031794;0.625102;,
  0.043611;-0.006901;0.999025;,
  0.998599;-0.052878;0.001739;,
  0.795893;-0.112609;-0.594873;,
  0.084953;-0.088759;-0.992424;,
  -0.735237;0.040920;-0.676574;,
  -0.995524;0.091839;-0.022313;,
  -0.759101;0.056483;0.648518;,
  -0.207451;-0.863540;0.459634;,
  -0.674713;-0.371195;0.637948;,
  0.019658;0.095366;0.995248;,
  -0.948890;-0.278538;0.148404;,
  -0.774124;-0.046373;-0.631333;,
  -0.024432;-0.170819;-0.984999;,
  0.720683;-0.186234;-0.667783;,
  0.985181;-0.116616;-0.125777;,
  0.742919;0.017978;0.669139;,
  0.693366;-0.278126;-0.664748;,
  -0.040322;-0.297384;-0.953906;,
  -0.775202;-0.119775;-0.620255;,
  -0.350505;0.064473;-0.934339;,
  -0.184212;-0.805373;0.563418;,
  -0.425000;-0.798818;0.425752;,
  -0.164764;-0.927256;0.336228;,
  0.038188;-0.892026;0.450367;,
  0.169618;-0.883470;0.436705;,
  0.074233;-0.898167;0.433343;,
  0.772674;0.634705;0.011189;,
  0.559044;0.825914;0.073051;,
  0.431041;0.894488;0.118723;;
  47;
  4;16,17,15,8;,
  4;18,16,8,9;,
  4;19,18,9,10;,
  4;20,19,10,11;,
  4;21,20,11,12;,
  4;22,21,12,13;,
  4;23,22,13,14;,
  4;17,23,14,15;,
  4;7,0,25,24;,
  4;24,25,17,16;,
  4;6,7,24,26;,
  4;26,24,16,18;,
  4;5,6,26,27;,
  4;27,26,18,19;,
  4;4,5,27,28;,
  4;28,27,19,20;,
  4;3,44,28,29;,
  4;29,28,20,21;,
  4;2,3,29,30;,
  4;30,29,21,22;,
  4;1,2,30,31;,
  4;31,30,22,23;,
  4;0,1,31,25;,
  4;25,31,23,17;,
  4;14,33,34,15;,
  4;13,35,33,14;,
  4;12,36,35,13;,
  4;11,37,36,12;,
  4;10,38,37,11;,
  4;9,39,38,10;,
  4;8,40,39,9;,
  4;15,34,40,8;,
  4;37,38,41,42;,
  4;36,37,42,43;,
  3;35,36,43;,
  3;38,39,41;,
  3;32,45,33;,
  3;32,33,35;,
  3;32,35,46;,
  3;32,46,47;,
  3;32,47,48;,
  3;32,48,49;,
  3;32,49,50;,
  3;32,50,45;,
  4;7,6,5,51;,
  4;52,7,51,52;,
  4;52,53,53,52;;
 }
 MeshTextureCoords {
  116;
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.500000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
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
  0.500000;1.000000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  1.000000;0.750000;;
 }
}
