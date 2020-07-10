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
 381;
 -0.72126;1.30165;1.29693;,
 -0.93681;-0.04414;1.44635;,
 0.05788;-0.13463;1.96035;,
 0.37275;1.17983;1.80736;,
 -1.50554;1.14250;0.04249;,
 -1.60485;-0.23552;0.49943;,
 -0.93681;-0.04414;1.44635;,
 -0.72126;1.30165;1.29693;,
 -0.92470;0.14614;-1.04494;,
 -1.08802;-1.06161;-0.58828;,
 -1.60485;-0.23552;0.49943;,
 -1.50554;1.14250;0.04249;,
 0.13040;-0.20951;-1.47667;,
 -0.04506;-1.44251;-1.00330;,
 -1.08802;-1.06161;-0.58828;,
 -0.92470;0.14614;-1.04494;,
 1.24122;-0.18018;-1.02033;,
 0.85514;-1.35623;-0.50548;,
 -0.04506;-1.44251;-1.00330;,
 0.13040;-0.20951;-1.47667;,
 1.75921;0.57790;0.06578;,
 1.53852;-0.89659;0.56221;,
 0.85514;-1.35623;-0.50548;,
 1.24122;-0.18018;-1.02033;,
 1.43854;0.90242;1.31340;,
 1.00635;-0.51159;1.49073;,
 1.53852;-0.89659;0.56221;,
 1.75921;0.57790;0.06578;,
 0.37275;1.17983;1.80736;,
 0.05788;-0.13463;1.96035;,
 1.00635;-0.51159;1.49073;,
 1.43854;0.90242;1.31340;,
 1.00635;-0.51159;1.49073;,
 -0.64130;-2.01976;2.31565;,
 0.64825;-2.24485;1.93438;,
 1.53852;-0.89659;0.56221;,
 0.64825;-2.24485;1.93438;,
 1.23767;-2.48014;1.32388;,
 0.85514;-1.35623;-0.50548;,
 1.23767;-2.48014;1.32388;,
 0.58581;-2.68851;0.03633;,
 -0.04506;-1.44251;-1.00330;,
 0.58581;-2.68851;0.03633;,
 -0.38184;-2.70890;-0.84824;,
 -1.08802;-1.06161;-0.58828;,
 -0.38184;-2.70890;-0.84824;,
 -1.21621;-2.63689;-0.52474;,
 -1.60485;-0.23552;0.49943;,
 -1.21621;-2.63689;-0.52474;,
 -1.88588;-2.40048;0.56619;,
 -0.93681;-0.04414;1.44635;,
 -1.88588;-2.40048;0.56619;,
 -1.68377;-2.12126;1.36611;,
 0.05788;-0.13463;1.96035;,
 -1.68377;-2.12126;1.36611;,
 -0.64130;-2.01976;2.31565;,
 -0.04589;-13.39590;-6.32203;,
 0.17974;-14.80928;-6.29672;,
 0.02414;-14.93950;-7.35615;,
 -0.11209;-13.42035;-7.17532;,
 -0.02167;-15.32274;-6.27180;,
 -0.10622;-15.42274;-7.13492;,
 -3.08352;-15.37551;-5.15233;,
 -3.20880;-14.94527;-5.06413;,
 -3.29254;-14.96797;-6.68078;,
 -3.15686;-15.40740;-6.53746;,
 -2.88254;-13.63953;-5.51338;,
 -3.16389;-13.56173;-6.57709;,
 -1.87709;-12.59392;1.23439;,
 -1.94654;-13.97964;1.30858;,
 -1.38545;-13.82998;2.67669;,
 -1.17059;-12.50206;2.32225;,
 -1.73093;-15.26406;1.29297;,
 -1.34094;-15.24954;2.61226;,
 -2.13843;-12.93819;-0.38252;,
 -2.52938;-14.12039;-0.24197;,
 -2.28362;-14.82650;-0.20202;,
 0.43555;-12.53325;0.91166;,
 0.63659;-14.03103;0.91648;,
 0.66206;-14.19339;-0.80842;,
 0.26936;-12.56912;-0.82381;,
 0.42671;-15.30070;0.96820;,
 0.43177;-14.79500;-0.67276;,
 0.06614;-12.51849;2.14522;,
 0.55932;-13.85266;2.38554;,
 0.46318;-15.24646;2.34249;,
 -2.88254;-13.63953;-5.51338;,
 -1.72558;-13.37499;-5.91358;,
 -1.97482;-13.41514;-7.32876;,
 -3.16389;-13.56173;-6.57709;,
 -0.04589;-13.39590;-6.32203;,
 -0.11209;-13.42035;-7.17532;,
 0.55932;-13.85266;2.38554;,
 -0.33008;-13.81251;3.04376;,
 -0.39071;-15.27870;2.77376;,
 0.46318;-15.24646;2.34249;,
 -1.38545;-13.82998;2.67669;,
 -1.34094;-15.24954;2.61226;,
 0.06614;-12.51849;2.14522;,
 -0.41062;-12.48292;2.70726;,
 -1.17059;-12.50206;2.32225;,
 -3.29254;-14.96797;-6.68078;,
 -2.01723;-14.96764;-7.64143;,
 -1.96976;-15.43377;-7.28127;,
 -3.15686;-15.40740;-6.53746;,
 0.02414;-14.93950;-7.35615;,
 -0.10622;-15.42274;-7.13492;,
 -3.16389;-13.56173;-6.57709;,
 -1.97482;-13.41514;-7.32876;,
 -0.11209;-13.42035;-7.17532;,
 -3.20880;-14.94527;-5.06413;,
 -3.12723;-14.72710;-4.42282;,
 -2.72304;-14.00273;-4.87414;,
 -3.08352;-15.37551;-5.15233;,
 -3.01977;-15.32830;-4.45460;,
 0.33944;-14.49976;-5.18122;,
 0.06554;-14.02190;-5.26391;,
 0.17974;-14.80928;-6.29672;,
 0.17459;-15.36482;-5.16245;,
 -0.02167;-15.32274;-6.27180;,
 -1.72558;-13.37499;-5.91358;,
 -1.36502;-13.67965;-5.07386;,
 0.06554;-14.02190;-5.26391;,
 -0.97155;-12.38848;-1.03669;,
 -2.88254;-13.63953;-5.51338;,
 -2.72304;-14.00273;-4.87414;,
 -2.13843;-12.93819;-0.38252;,
 0.43555;-12.53325;0.91166;,
 0.26936;-12.56912;-0.82381;,
 -0.28206;-10.96189;0.13186;,
 0.18064;-10.98901;0.92594;,
 0.26936;-12.56912;-0.82381;,
 -0.97155;-12.38848;-1.03669;,
 -0.83689;-10.92986;-0.15463;,
 -0.28206;-10.96189;0.13186;,
 -0.97155;-12.38848;-1.03669;,
 -2.13843;-12.93819;-0.38252;,
 -1.30076;-10.94153;0.26674;,
 -0.83689;-10.92986;-0.15463;,
 -2.13843;-12.93819;-0.38252;,
 -1.87709;-12.59392;1.23439;,
 -1.66450;-10.98901;0.86550;,
 -1.30076;-10.94153;0.26674;,
 -1.87709;-12.59392;1.23439;,
 -1.17059;-12.50206;2.32225;,
 -1.09446;-11.01264;1.89876;,
 -1.66450;-10.98901;0.86550;,
 -1.17059;-12.50206;2.32225;,
 -0.41062;-12.48292;2.70726;,
 -0.54142;-10.94586;2.09904;,
 -1.09446;-11.01264;1.89876;,
 -0.41062;-12.48292;2.70726;,
 0.06614;-12.51849;2.14522;,
 -0.16566;-10.97539;1.67855;,
 -0.54142;-10.94586;2.09904;,
 0.06614;-12.51849;2.14522;,
 0.43555;-12.53325;0.91166;,
 0.18064;-10.98901;0.92594;,
 -0.16566;-10.97539;1.67855;,
 -1.94043;-2.11168;1.53595;,
 -0.67762;-2.01664;2.61385;,
 -0.64130;-2.01976;2.31565;,
 -1.68377;-2.12126;1.36611;,
 -0.79227;-4.11198;2.59166;,
 -1.93094;-4.38900;2.05905;,
 -1.67429;-4.39857;1.88921;,
 -0.75595;-4.11509;2.29346;,
 -2.18805;-2.39596;0.49974;,
 -1.94043;-2.11168;1.53595;,
 -1.68377;-2.12126;1.36611;,
 -1.88588;-2.40048;0.56619;,
 -1.93094;-4.38900;2.05905;,
 -2.16919;-5.62895;0.21462;,
 -1.86702;-5.63346;0.28107;,
 -1.67429;-4.39857;1.88921;,
 -1.40476;-2.63760;-0.78048;,
 -2.18805;-2.39596;0.49974;,
 -1.88588;-2.40048;0.56619;,
 -1.21621;-2.63689;-0.52474;,
 -2.16919;-5.62895;0.21462;,
 -1.48525;-6.50894;-0.70165;,
 -1.29670;-6.34263;-0.44591;,
 -1.86702;-5.63346;0.28107;,
 -0.31711;-2.73151;-1.12726;,
 -1.40476;-2.63760;-0.78048;,
 -1.21621;-2.63689;-0.52474;,
 -0.38184;-2.70890;-0.84824;,
 -1.48525;-6.50894;-0.70165;,
 -0.61223;-7.88242;-0.88313;,
 -0.67696;-6.35537;-0.60411;,
 -1.29670;-6.34263;-0.44591;,
 0.85150;-2.73282;-0.15422;,
 -0.31711;-2.73151;-1.12726;,
 -0.38184;-2.70890;-0.84824;,
 0.58581;-2.68851;0.03633;,
 -0.61223;-7.88242;-0.88313;,
 0.22749;-6.60556;-0.13211;,
 -0.03820;-6.39565;0.05844;,
 -0.67696;-6.35537;-0.60411;,
 1.52881;-2.53130;1.33902;,
 0.85150;-2.73282;-0.15422;,
 0.58581;-2.68851;0.03633;,
 1.23767;-2.48014;1.32388;,
 0.22749;-6.60556;-0.13211;,
 0.70588;-6.02205;1.07368;,
 0.41474;-5.97088;1.05854;,
 -0.03820;-6.39565;0.05844;,
 0.84513;-2.27555;2.17869;,
 1.52881;-2.53130;1.33902;,
 1.23767;-2.48014;1.32388;,
 0.64825;-2.24485;1.93438;,
 0.70588;-6.02205;1.07368;,
 0.39914;-4.54598;2.14082;,
 0.20226;-4.51527;1.89651;,
 0.41474;-5.97088;1.05854;,
 -0.67762;-2.01664;2.61385;,
 0.84513;-2.27555;2.17869;,
 0.64825;-2.24485;1.93438;,
 -0.64130;-2.01976;2.31565;,
 0.39914;-4.54598;2.14082;,
 -0.79227;-4.11198;2.59166;,
 -0.75595;-4.11509;2.29346;,
 0.20226;-4.51527;1.89651;,
 -2.28319;-2.09872;1.76389;,
 -0.72954;-2.01175;3.01531;,
 -2.27370;-4.37604;2.28699;,
 -0.84419;-4.10709;2.99312;,
 -2.59445;-2.39008;0.41302;,
 -2.28319;-2.09872;1.76389;,
 -2.57559;-5.62306;0.12790;,
 -2.27370;-4.37604;2.28699;,
 -1.64762;-2.63928;-1.12386;,
 -2.59445;-2.39008;0.41302;,
 -1.72811;-7.06804;-1.04503;,
 -2.57559;-5.62306;0.12790;,
 -0.22919;-2.76183;-1.51360;,
 -1.64762;-2.63928;-1.12386;,
 -0.52431;-8.36437;-1.26947;,
 -1.72811;-7.06804;-1.04503;,
 1.20113;-2.79238;-0.40969;,
 -0.22919;-2.76183;-1.51360;,
 0.57712;-7.22253;-0.38758;,
 -0.52431;-8.36437;-1.26947;,
 1.92614;-2.60103;1.36229;,
 1.20113;-2.79238;-0.40969;,
 1.10321;-6.09178;1.09695;,
 0.57712;-7.22253;-0.38758;,
 1.10806;-2.31655;2.50128;,
 1.92614;-2.60103;1.36229;,
 0.66207;-4.58697;2.46341;,
 1.10321;-6.09178;1.09695;,
 -0.72954;-2.01175;3.01531;,
 1.10806;-2.31655;2.50128;,
 -0.84419;-4.10709;2.99312;,
 0.66207;-4.58697;2.46341;,
 0.77740;-10.09721;0.94054;,
 -0.28206;-10.96189;0.13186;,
 0.04103;-10.12504;-0.36949;,
 0.04103;-10.12504;-0.36949;,
 -0.83689;-10.92986;-0.15463;,
 -0.86376;-10.18327;-0.89764;,
 -0.86376;-10.18327;-0.89764;,
 -1.30076;-10.94153;0.26674;,
 -1.63217;-10.17734;-0.35025;,
 -1.63217;-10.17734;-0.35025;,
 -1.66450;-10.98901;0.86550;,
 -2.25294;-10.22797;0.69362;,
 -0.20633;-9.39071;0.10906;,
 -0.03820;-6.39565;0.05844;,
 0.41474;-5.97088;1.05854;,
 0.25160;-9.35124;0.96613;,
 -0.78990;-9.43260;-0.28670;,
 -0.67696;-6.35537;-0.60411;,
 -0.03820;-6.39565;0.05844;,
 -0.20633;-9.39071;0.10906;,
 -1.29955;-9.45175;0.05396;,
 -1.29670;-6.34263;-0.44591;,
 -0.67696;-6.35537;-0.60411;,
 -0.78990;-9.43260;-0.28670;,
 -1.71986;-9.40837;0.70574;,
 -1.86702;-5.63346;0.28107;,
 -1.29670;-6.34263;-0.44591;,
 -1.29955;-9.45175;0.05396;,
 -1.23386;-9.42251;1.89647;,
 -1.67429;-4.39857;1.88921;,
 -1.86702;-5.63346;0.28107;,
 -1.71986;-9.40837;0.70574;,
 -2.25294;-10.22797;0.69362;,
 -1.41798;-10.22517;2.45462;,
 -0.45880;-10.14279;2.80511;,
 -0.16566;-10.97539;1.67855;,
 0.23724;-10.10319;2.14497;,
 0.23724;-10.10319;2.14497;,
 0.18064;-10.98901;0.92594;,
 0.77740;-10.09721;0.94054;,
 -1.41798;-10.22517;2.45462;,
 -0.54142;-10.94586;2.09904;,
 -0.45880;-10.14279;2.80511;,
 -2.25294;-10.22797;0.69362;,
 -1.09446;-11.01264;1.89876;,
 -1.41798;-10.22517;2.45462;,
 -0.10474;-9.41469;1.71464;,
 0.20226;-4.51527;1.89651;,
 -0.75595;-4.11509;2.29346;,
 -0.57311;-9.44576;2.12776;,
 0.25160;-9.35124;0.96613;,
 0.41474;-5.97088;1.05854;,
 0.20226;-4.51527;1.89651;,
 -0.10474;-9.41469;1.71464;,
 -0.57311;-9.44576;2.12776;,
 -0.75595;-4.11509;2.29346;,
 -1.67429;-4.39857;1.88921;,
 -1.23386;-9.42251;1.89647;,
 -0.09261;-15.69145;-7.12128;,
 -1.96673;-15.70276;-7.27276;,
 -1.96976;-15.43377;-7.28127;,
 -0.00926;-15.59167;-6.26626;,
 -1.72152;-15.70766;-5.82553;,
 -3.16441;-15.67667;-6.53407;,
 -3.09018;-15.64456;-5.14239;,
 -3.08352;-15.37551;-5.15233;,
 -3.15686;-15.40740;-6.53746;,
 0.44691;-15.47311;-0.87057;,
 0.18777;-15.63385;-5.16094;,
 0.17459;-15.36482;-5.16245;,
 0.43177;-14.79500;-0.67276;,
 -0.92527;-15.59004;-0.67394;,
 -0.92656;-14.91188;-0.38791;,
 -1.38102;-15.66201;-4.83613;,
 -1.72152;-15.70766;-5.82553;,
 -3.02894;-15.59722;-4.44288;,
 -2.29618;-15.50470;-0.39847;,
 -2.28362;-14.82650;-0.20202;,
 -3.01977;-15.32830;-4.45460;,
 -3.09018;-15.64456;-5.14239;,
 0.44584;-15.43006;-0.56138;,
 -0.92825;-15.54695;-0.27155;,
 0.44126;-15.52655;0.96768;,
 0.42671;-15.30070;0.96820;,
 -0.63247;-15.59096;1.26832;,
 -2.30107;-15.46156;-0.08069;,
 -1.74713;-15.48988;1.29838;,
 -1.73093;-15.26406;1.29297;,
 -0.39067;-15.50450;2.78431;,
 0.47822;-15.47230;2.35209;,
 0.46318;-15.24646;2.34249;,
 -0.39071;-15.27870;2.77376;,
 -1.35590;-15.47530;2.62376;,
 -1.34094;-15.24954;2.61226;,
 -2.25529;-4.52600;2.33908;,
 -0.85659;-4.26521;3.00646;,
 -0.80467;-4.27010;2.60501;,
 -1.91253;-4.53895;2.11114;,
 -2.56936;-5.74834;0.23054;,
 -2.25529;-4.52600;2.33908;,
 -1.91253;-4.53895;2.11114;,
 -2.16296;-5.75422;0.31726;,
 -1.76522;-7.16302;-0.92387;,
 -2.56936;-5.74834;0.23054;,
 -2.16296;-5.75422;0.31726;,
 -1.52236;-6.60392;-0.58048;,
 -0.56630;-8.44760;-1.13939;,
 -1.76522;-7.16302;-0.92387;,
 -1.52236;-6.60392;-0.58048;,
 -0.65423;-7.96566;-0.75305;,
 0.54232;-7.32633;-0.27190;,
 -0.56630;-8.44760;-1.13939;,
 -0.65423;-7.96566;-0.75305;,
 0.19270;-6.70937;-0.01643;,
 1.03592;-6.20312;1.19559;,
 0.54232;-7.32633;-0.27190;,
 0.19270;-6.70937;-0.01643;,
 0.63859;-6.13339;1.17232;,
 0.60011;-4.71619;2.51918;,
 1.03592;-6.20312;1.19559;,
 0.63859;-6.13339;1.17232;,
 0.33718;-4.67520;2.19660;,
 -0.85659;-4.26521;3.00646;,
 0.60011;-4.71619;2.51918;,
 0.33718;-4.67520;2.19660;,
 -0.80467;-4.27010;2.60501;;
 
 166;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,29,33,34;,
 4;35,25,36,37;,
 4;38,21,39,40;,
 4;41,17,42,43;,
 4;44,13,45,46;,
 4;47,9,48,49;,
 4;50,5,51,52;,
 4;53,1,54,55;,
 4;56,57,58,59;,
 4;57,60,61,58;,
 4;62,63,64,65;,
 4;63,66,67,64;,
 4;68,69,70,71;,
 4;69,72,73,70;,
 4;74,75,69,68;,
 4;75,76,72,69;,
 4;77,78,79,80;,
 4;78,81,82,79;,
 4;83,84,78,77;,
 4;84,85,81,78;,
 4;86,87,88,89;,
 4;87,90,91,88;,
 4;92,93,94,95;,
 4;93,96,97,94;,
 4;98,99,93,92;,
 4;99,100,96,93;,
 4;101,102,103,104;,
 4;102,105,106,103;,
 4;107,108,102,101;,
 4;108,109,105,102;,
 4;110,111,112,66;,
 4;111,75,74,112;,
 4;113,114,111,110;,
 4;114,76,75,111;,
 4;79,115,116,80;,
 4;115,117,56,116;,
 4;82,118,115,79;,
 4;118,119,117,115;,
 4;120,121,122,90;,
 4;121,123,80,122;,
 4;124,125,121,120;,
 4;125,126,123,121;,
 4;127,128,129,130;,
 4;131,132,133,134;,
 4;135,136,137,138;,
 4;139,140,141,142;,
 4;143,144,145,146;,
 4;147,148,149,150;,
 4;151,152,153,154;,
 4;155,156,157,158;,
 4;159,160,161,162;,
 4;163,164,165,166;,
 4;167,168,169,170;,
 4;171,172,173,174;,
 4;175,176,177,178;,
 4;179,180,181,182;,
 4;183,184,185,186;,
 4;187,188,189,190;,
 4;191,192,193,194;,
 4;195,196,197,198;,
 4;199,200,201,202;,
 4;203,204,205,206;,
 4;207,208,209,210;,
 4;211,212,213,214;,
 4;215,216,217,218;,
 4;219,220,221,222;,
 4;223,224,160,159;,
 4;224,223,225,226;,
 4;227,228,168,167;,
 4;228,227,229,230;,
 4;231,232,176,175;,
 4;232,231,233,234;,
 4;235,236,184,183;,
 4;236,235,237,238;,
 4;239,240,192,191;,
 4;240,239,241,242;,
 4;243,244,200,199;,
 4;244,243,245,246;,
 4;247,248,208,207;,
 4;248,247,249,250;,
 4;251,252,216,215;,
 4;252,251,253,254;,
 4;255,157,256,257;,
 4;258,129,259,260;,
 4;261,133,262,263;,
 4;264,137,265,266;,
 4;267,268,269,270;,
 4;267,270,255,257;,
 4;271,272,273,274;,
 4;271,274,258,260;,
 4;275,276,277,278;,
 4;275,278,261,263;,
 4;279,280,281,282;,
 4;279,282,264,266;,
 4;283,284,285,286;,
 4;283,286,287,288;,
 4;289,149,290,291;,
 4;292,153,293,294;,
 4;295,145,296,297;,
 4;298,141,299,300;,
 4;301,302,303,304;,
 4;301,304,289,291;,
 4;305,306,307,308;,
 4;305,308,292,294;,
 4;309,310,311,312;,
 4;309,312,295,297;,
 4;313,314,315,106;,
 4;316,313,106,119;,
 4;316,317,314,313;,
 4;318,319,320,321;,
 4;314,318,321,315;,
 4;317,319,318,314;,
 4;322,323,324,325;,
 4;326,322,325,327;,
 4;326,328,323,322;,
 4;323,316,119,324;,
 4;328,329,316,323;,
 4;330,331,332,333;,
 4;331,326,327,332;,
 4;331,330,328,326;,
 4;334,330,333,113;,
 4;330,334,329,328;,
 4;335,336,327,325;,
 4;337,335,325,338;,
 4;337,339,336,335;,
 4;340,341,342,332;,
 4;336,340,332,327;,
 4;339,341,340,336;,
 4;343,344,345,346;,
 4;344,337,338,345;,
 4;344,343,339,337;,
 4;347,343,346,348;,
 4;341,347,348,342;,
 4;343,347,341,339;,
 4;349,350,226,225;,
 4;351,352,164,163;,
 4;350,349,352,351;,
 4;353,354,230,229;,
 4;355,356,172,171;,
 4;354,353,356,355;,
 4;357,358,234,233;,
 4;359,360,180,179;,
 4;358,357,360,359;,
 4;361,362,238,237;,
 4;363,364,188,187;,
 4;362,361,364,363;,
 4;365,366,242,241;,
 4;367,368,196,195;,
 4;366,365,368,367;,
 4;369,370,246,245;,
 4;371,372,204,203;,
 4;370,369,372,371;,
 4;373,374,250,249;,
 4;375,376,212,211;,
 4;374,373,376,375;,
 4;377,378,254,253;,
 4;379,380,220,219;,
 4;378,377,380,379;;
 
 MeshMaterialList {
  14;
  166;
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5;;
  Material {
   0.512000;0.512000;0.512000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.605600;0.009600;0.000000;1.000000;;
   17.000000;
   0.130000;0.130000;0.130000;;
   0.068130;0.001080;0.000000;;
  }
  Material {
   0.179200;0.439200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.040800;0.040800;0.040800;1.000000;;
   7.000000;
   0.110000;0.110000;0.110000;;
   0.002550;0.002550;0.002550;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.596000;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.248000;0.097600;0.044000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.084800;0.279200;0.460800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.432800;0.295200;0.021600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.668000;0.555200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.659200;0.000000;1.000000;;
   28.000000;
   0.150000;0.150000;0.150000;;
   0.180000;0.148320;0.000000;;
  }
  Material {
   0.501600;0.501600;0.501600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.238400;0.200800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.019200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  248;
  -0.041733;0.152351;0.987445;,
  -0.706756;0.227181;0.669989;,
  -0.992190;0.124197;-0.011609;,
  -0.687218;-0.068483;-0.723216;,
  0.048960;-0.296251;-0.953855;,
  0.712556;-0.375487;-0.592683;,
  0.975159;-0.207009;0.078819;,
  0.670486;0.007261;0.741887;,
  -0.649799;0.206364;0.731556;,
  0.006056;0.097593;0.995208;,
  -0.994066;0.091625;0.058631;,
  0.970466;-0.237158;0.044186;,
  0.715698;-0.061494;0.695697;,
  0.692611;-0.402219;-0.598756;,
  -0.015059;-0.382171;-0.923969;,
  -0.717212;-0.169176;-0.676008;,
  0.620850;0.073987;0.780430;,
  0.807651;0.045073;0.587935;,
  0.731026;-0.349282;-0.586177;,
  0.566957;-0.339258;-0.750643;,
  -0.648350;0.032552;-0.760646;,
  -0.984626;0.155251;-0.080056;,
  -0.758480;0.246318;0.603354;,
  -0.090558;0.207715;0.973988;,
  -0.073327;-0.991870;0.104009;,
  0.145161;-0.917975;0.369122;,
  -0.037467;-0.796498;0.603479;,
  -0.072159;-0.682846;0.726990;,
  -0.252796;-0.592832;0.764620;,
  -0.377774;-0.716528;0.586408;,
  -0.360992;-0.706606;0.608599;,
  -0.437634;-0.799538;0.411357;,
  0.834329;-0.171598;0.523879;,
  0.984819;-0.173304;-0.009894;,
  0.725075;-0.097844;-0.681684;,
  -0.160835;0.557389;-0.814524;,
  -0.801733;0.413590;-0.431470;,
  -0.962202;-0.002333;0.272326;,
  -0.646909;-0.199051;0.736130;,
  -0.343300;-0.192195;0.919351;,
  -0.668280;-0.022981;0.743554;,
  -0.989315;-0.117552;0.086243;,
  0.983413;-0.133482;-0.122810;,
  0.862266;-0.032976;0.505381;,
  -0.659308;0.238521;0.713037;,
  -0.939770;0.295053;0.172559;,
  0.967011;0.221368;-0.126042;,
  0.844669;0.263453;0.465969;,
  -0.958040;-0.097530;0.269530;,
  0.993413;-0.112417;-0.022191;,
  -0.841923;0.512429;-0.169063;,
  0.862735;0.369748;-0.344927;,
  0.984140;0.131376;-0.119201;,
  -0.974136;0.164729;0.154671;,
  0.984843;-0.147972;-0.090495;,
  -0.875577;-0.221967;-0.429063;,
  -0.942186;-0.042382;0.332400;,
  0.997741;-0.067181;-0.000068;,
  -0.936648;0.231449;0.262910;,
  0.972359;0.230663;0.036220;,
  -0.989692;0.015596;0.142364;,
  -0.679858;0.056503;0.731164;,
  0.991846;-0.044999;-0.119231;,
  0.874463;0.084433;0.477688;,
  -0.977873;0.033775;0.206456;,
  0.998679;0.003069;-0.051302;,
  0.989457;-0.104691;-0.100078;,
  -0.992258;-0.061416;0.107942;,
  -0.939822;0.005959;0.341613;,
  0.999389;0.017199;0.030429;,
  0.148496;-0.029890;0.988461;,
  -0.019969;0.974661;0.222795;,
  0.698760;0.288639;0.654540;,
  0.164100;-0.329200;0.929892;,
  -0.137217;0.812593;-0.566449;,
  -0.074841;0.997098;0.013926;,
  -0.230858;-0.289867;-0.928807;,
  0.161379;0.090729;0.982713;,
  -0.243647;-0.198801;-0.949270;,
  -0.982109;-0.114231;0.149713;,
  0.987787;-0.117953;-0.101806;,
  -0.651111;0.747211;0.133151;,
  0.771170;0.601356;-0.208969;,
  -0.984813;0.089290;0.148899;,
  0.993762;0.030502;-0.107267;,
  -0.032848;0.995744;0.086113;,
  0.195446;0.979073;-0.056727;,
  0.167842;0.974649;-0.147946;,
  0.094039;0.986397;-0.134826;,
  0.071176;0.994786;-0.073036;,
  0.078151;0.992382;-0.095237;,
  0.027109;0.980150;-0.196397;,
  -0.034285;0.987345;-0.154834;,
  0.067684;0.997412;-0.024251;,
  0.191846;0.980169;-0.049640;,
  0.167221;0.976673;-0.134708;,
  0.098511;0.987056;-0.126553;,
  0.074400;0.994667;-0.071425;,
  0.075864;0.993014;-0.090380;,
  0.026781;0.983793;-0.177295;,
  -0.028169;0.989890;-0.139015;,
  0.070049;0.997297;-0.022194;,
  -0.099833;0.101746;0.989788;,
  -0.823864;0.081833;0.560848;,
  -0.986255;-0.053954;-0.156176;,
  -0.715729;-0.201840;-0.668575;,
  0.221855;-0.056188;-0.973459;,
  0.877242;-0.338356;-0.340531;,
  0.945906;-0.255538;0.199906;,
  0.620453;-0.076828;0.780471;,
  -0.568497;-0.639512;-0.517529;,
  -0.047942;-0.697715;-0.714770;,
  0.580314;-0.573805;-0.577913;,
  -0.960699;0.257551;-0.103561;,
  -0.663719;0.251626;-0.704387;,
  0.560839;0.264106;-0.784670;,
  0.728757;0.265501;-0.631207;,
  0.206393;-0.656072;0.725928;,
  -0.572726;0.579879;0.579418;,
  0.823367;-0.566021;-0.041069;,
  0.685460;-0.557428;0.468422;,
  -0.771086;-0.635977;-0.030984;,
  0.115503;0.349520;0.929782;,
  -0.689383;0.292893;0.662544;,
  0.959161;0.281558;-0.027111;,
  0.739900;0.295195;0.604490;,
  -0.997114;0.030228;0.069642;,
  0.989467;0.044522;-0.137744;,
  -0.984414;0.004517;0.175810;,
  0.997077;0.044458;-0.062143;,
  0.079599;-0.038546;-0.996082;,
  -0.998243;0.027646;0.052413;,
  0.010785;-0.999526;0.028851;,
  -0.236120;-0.027822;-0.971326;,
  -0.991143;0.018679;0.131476;,
  0.992040;0.044568;-0.117771;,
  0.007766;-0.999653;0.025155;,
  -0.163990;0.053564;0.985007;,
  0.445787;0.054816;0.893459;,
  -0.924511;0.085662;0.371404;,
  -0.188264;-0.175104;-0.966382;,
  -0.941558;0.081195;0.326920;,
  0.998464;0.054460;-0.010170;,
  0.148113;0.056965;0.987328;,
  -0.166928;-0.177533;-0.969854;,
  -0.003855;-0.999945;0.009736;,
  0.034410;-0.166326;-0.985470;,
  0.811846;-0.094741;-0.576134;,
  0.980691;0.146524;0.129521;,
  0.820307;0.340882;0.459233;,
  0.747246;0.407718;0.524776;,
  -0.859528;0.500477;0.103606;,
  -0.914488;0.349355;-0.204114;,
  -0.666569;0.019373;-0.745191;,
  -0.053882;0.167929;0.984325;,
  -0.813783;0.095965;0.573192;,
  -0.986210;-0.124392;-0.109159;,
  -0.795931;-0.379474;-0.471692;,
  -0.649595;-0.508352;-0.565336;,
  0.851584;-0.514110;-0.102446;,
  0.919707;-0.305027;0.247178;,
  0.660351;-0.020147;0.750686;,
  0.855570;-0.340421;-0.390017;,
  -0.368115;-0.011089;-0.929714;,
  -0.132396;0.957655;0.255672;,
  -0.154316;0.986381;0.056906;,
  0.093548;0.977986;0.186527;,
  0.005254;0.999561;-0.029170;,
  -0.389736;0.271047;0.880136;,
  -0.563581;-0.178387;-0.806570;,
  0.110463;-0.194539;-0.974655;,
  0.092106;-0.292153;-0.951926;,
  -0.570195;0.146852;-0.808277;,
  -0.246514;0.164873;-0.955012;,
  0.108382;0.162016;-0.980818;,
  0.176716;0.902831;0.392005;,
  0.185070;0.931085;-0.314372;,
  0.733302;-0.152111;0.662670;,
  0.065317;0.997518;-0.026310;,
  -0.040408;0.984503;-0.170651;,
  0.027427;0.976127;-0.215463;,
  0.080437;0.991721;-0.100093;,
  0.067952;0.994892;-0.074647;,
  0.089556;0.985649;-0.143092;,
  0.168433;0.972449;-0.161164;,
  0.199036;0.977912;-0.063816;,
  -0.145656;0.034118;0.988747;,
  -0.833243;0.068155;0.548690;,
  -0.978821;0.019551;-0.203783;,
  -0.572925;0.000650;-0.819608;,
  0.822666;-0.126033;-0.554380;,
  0.968340;-0.200985;0.148060;,
  0.577749;-0.132172;0.805442;,
  -0.656735;-0.616700;-0.434027;,
  0.788793;-0.063583;-0.611362;,
  0.997948;-0.059789;-0.022935;,
  0.809018;0.587112;-0.028092;,
  0.586394;0.565523;-0.579935;,
  0.643737;-0.079026;-0.761155;,
  -0.032858;0.644466;-0.763927;,
  -0.644185;-0.105769;-0.757522;,
  -0.403330;-0.112939;-0.908058;,
  -0.468497;0.253936;-0.846184;,
  -0.599371;0.567815;-0.564216;,
  -0.986815;-0.071545;-0.145177;,
  -0.829491;0.556198;-0.050879;,
  -0.735441;-0.041607;0.676310;,
  -0.508137;-0.619311;0.598540;,
  0.757258;-0.055893;0.650720;,
  0.092716;-0.043595;0.994738;,
  0.120025;0.679344;0.723938;,
  0.634553;0.599828;0.487390;,
  0.993762;0.044448;-0.102280;,
  0.045961;-0.998727;0.020793;,
  0.011459;-0.999427;0.031836;,
  0.050533;-0.997417;0.051049;,
  -0.528130;-0.014304;-0.849043;,
  -0.024399;-0.999022;0.036871;,
  -0.027637;-0.999539;0.012563;,
  0.191773;-0.326616;0.925497;,
  0.005421;-0.999687;0.024443;,
  0.048541;-0.998802;0.006192;,
  0.055722;-0.998207;0.021865;,
  0.136297;-0.331524;0.933550;,
  -0.044893;-0.998628;0.026960;,
  -0.033027;-0.998482;0.044068;,
  0.998987;0.044138;0.008761;,
  0.062913;-0.998011;-0.004051;,
  -0.007868;-0.999606;-0.026934;,
  0.060365;-0.996908;-0.050301;,
  -0.145513;-0.179878;-0.972867;,
  -0.070558;-0.997232;0.023469;,
  -0.076060;-0.997097;-0.003427;,
  0.997477;0.064757;-0.029097;,
  0.065327;-0.996971;0.042207;,
  0.000162;-0.998924;0.046376;,
  -0.956448;0.076542;0.281688;,
  -0.065003;-0.996614;0.050348;,
  -0.074178;-0.993749;0.083432;,
  0.115232;-0.937877;0.327274;,
  0.039807;-0.773238;0.632865;,
  -0.233853;-0.600961;0.764303;,
  -0.263137;-0.519436;0.812985;,
  0.775819;-0.594757;-0.210642;,
  -0.856789;0.502558;0.115530;,
  -0.219718;-0.652699;0.725057;,
  -0.414590;-0.679361;0.605461;,
  -0.401279;-0.839631;0.366053;;
  166;
  4;8,1,0,9;,
  4;10,2,1,8;,
  4;15,3,2,10;,
  4;14,4,3,15;,
  4;13,5,4,14;,
  4;11,6,5,13;,
  4;12,7,6,11;,
  4;9,0,7,12;,
  4;7,0,23,16;,
  4;6,7,16,17;,
  4;5,6,162,18;,
  4;4,5,18,19;,
  4;3,4,163,20;,
  4;2,3,20,21;,
  4;1,2,21,22;,
  4;0,1,22,23;,
  4;46,62,66,52;,
  4;62,42,54,66;,
  4;41,60,67,55;,
  4;60,45,53,67;,
  4;58,68,61,44;,
  4;68,56,40,61;,
  4;50,64,68,58;,
  4;64,48,56,68;,
  4;59,69,65,51;,
  4;69,57,49,65;,
  4;47,63,69,59;,
  4;63,43,57,69;,
  4;164,71,75,165;,
  4;71,166,167,75;,
  4;63,77,70,43;,
  4;77,61,40,70;,
  4;47,72,77,63;,
  4;168,44,61,77;,
  4;169,78,76,55;,
  4;78,170,171,76;,
  4;172,173,78,169;,
  4;173,174,170,78;,
  4;60,83,81,45;,
  4;83,64,50,81;,
  4;41,79,83,60;,
  4;79,48,64,83;,
  4;65,84,82,51;,
  4;84,62,46,82;,
  4;49,80,84,65;,
  4;80,42,62,84;,
  4;71,85,175,166;,
  4;85,74,176,82;,
  4;164,81,85,71;,
  4;81,50,74,85;,
  4;59,51,34,33;,
  4;51,74,35,34;,
  4;74,50,36,35;,
  4;50,58,37,36;,
  4;58,44,38,37;,
  4;44,168,39,38;,
  4;72,47,32,177;,
  4;47,59,33,32;,
  4;92,93,178,179;,
  4;24,25,25,24;,
  4;91,92,179,180;,
  4;25,26,26,25;,
  4;90,91,180,181;,
  4;26,27,27,26;,
  4;89,90,181,182;,
  4;27,28,28,27;,
  4;88,89,182,183;,
  4;28,29,29,28;,
  4;87,88,183,184;,
  4;29,30,30,29;,
  4;86,87,184,185;,
  4;30,31,31,30;,
  4;93,86,185,178;,
  4;31,24,24,31;,
  4;100,101,93,92;,
  4;186,187,103,102;,
  4;99,100,92,91;,
  4;187,188,104,103;,
  4;98,99,91,90;,
  4;188,189,105,104;,
  4;97,98,90,89;,
  4;189,106,106,105;,
  4;96,97,89,88;,
  4;106,190,107,106;,
  4;95,96,88,87;,
  4;190,191,108,107;,
  4;94,95,87,86;,
  4;191,192,109,108;,
  4;101,94,86,93;,
  4;192,186,102,109;,
  4;119,33,34,112;,
  4;112,34,111,111;,
  4;111,111,110,110;,
  4;110,110,193,121;,
  4;116,194,195,124;,
  4;116,124,196,197;,
  4;115,198,194,116;,
  4;115,116,197,199;,
  4;114,200,201,202;,
  4;114,202,199,203;,
  4;113,204,200,114;,
  4;113,114,203,205;,
  4;123,206,204,113;,
  4;123,113,205,118;,
  4;117,177,32,120;,
  4;120,32,33,119;,
  4;207,38,39,117;,
  4;121,37,38,207;,
  4;125,208,209,122;,
  4;125,122,210,211;,
  4;124,195,208,125;,
  4;124,125,211,196;,
  4;122,209,206,123;,
  4;122,123,118,210;,
  4;130,133,76,171;,
  4;127,212,54,42;,
  4;213,132,214,215;,
  4;131,126,41,55;,
  4;133,216,55,76;,
  4;132,217,218,214;,
  4;129,135,80,49;,
  4;73,219,219,73;,
  4;220,136,221,222;,
  4;135,127,42,80;,
  4;136,132,213,221;,
  4;134,128,48,79;,
  4;223,73,73,223;,
  4;224,225,136,220;,
  4;126,134,79,41;,
  4;225,217,132,136;,
  4;140,144,144,140;,
  4;142,226,49,57;,
  4;227,145,228,229;,
  4;139,141,56,48;,
  4;144,230,230,144;,
  4;145,231,232,228;,
  4;143,138,43,70;,
  4;233,142,57,43;,
  4;234,235,145,227;,
  4;137,143,70,40;,
  4;141,236,40,56;,
  4;235,237,231,145;,
  4;155,154,102,103;,
  4;146,147,147,146;,
  4;238,239,239,238;,
  4;156,155,103,104;,
  4;147,148,148,147;,
  4;239,240,240,239;,
  4;157,156,104,105;,
  4;148,149,149,148;,
  4;240,241,241,240;,
  4;158,157,105,158;,
  4;149,150,150,149;,
  4;241,242,242,241;,
  4;159,243,243,107;,
  4;244,151,151,244;,
  4;242,245,245,242;,
  4;160,159,107,108;,
  4;151,152,152,151;,
  4;245,246,246,245;,
  4;161,160,108,109;,
  4;152,153,153,152;,
  4;246,247,247,246;,
  4;154,161,109,102;,
  4;153,146,146,153;,
  4;247,238,238,247;;
 }
 MeshTextureCoords {
  381;
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.250000;-0.000000;,
  0.000000;0.000000;,
  0.500000;1.000000;,
  0.500000;-0.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  0.750000;-0.000000;,
  0.500000;-0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.000000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.500000;,
  0.500000;-0.000000;,
  0.750000;1.000000;,
  0.750000;0.500000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.750000;0.000000;,
  0.500000;-0.000000;,
  1.000000;1.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.500000;-0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;-0.000000;,
  0.000000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;-0.000000;,
  0.000000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  0.750000;1.000000;,
  1.000000;0.000000;,
  0.750000;0.000000;,
  0.250000;0.500000;,
  0.250000;1.000000;,
  0.000000;0.500000;,
  0.250000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  0.750000;1.000000;,
  0.500000;0.500000;,
  1.000000;0.000000;,
  0.750000;0.000000;,
  0.500000;-0.000000;,
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
  0.000000;1.000000;,
  -0.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  -0.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  -0.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  -0.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  -0.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  -0.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  -0.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  -0.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  -0.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.852950;1.000000;,
  1.000000;0.750000;,
  0.860390;0.750000;,
  0.860390;1.000000;,
  1.000000;0.750000;,
  0.875640;0.750000;,
  0.875640;1.000000;,
  1.000000;0.750000;,
  0.869160;0.750000;,
  0.869160;1.000000;,
  1.000000;0.750000;,
  0.871090;0.750000;,
  0.689440;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  0.696900;1.000000;,
  0.706160;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  0.689440;1.000000;,
  0.701420;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  0.706160;1.000000;,
  0.726640;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  0.701420;1.000000;,
  0.759580;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  0.726640;1.000000;,
  0.871090;1.000000;,
  0.877430;0.750000;,
  0.902490;1.000000;,
  1.000000;0.750000;,
  0.888470;0.750000;,
  0.888470;1.000000;,
  1.000000;0.750000;,
  0.853330;0.750000;,
  0.899010;1.000000;,
  1.000000;0.750000;,
  0.902490;0.750000;,
  0.897320;1.000000;,
  1.000000;0.750000;,
  0.899010;0.750000;,
  0.834420;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  0.852280;1.000000;,
  0.783170;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  0.834420;1.000000;,
  0.852280;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  0.847830;1.000000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.000000;,
  0.000000;0.250000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.250000;,
  0.000000;0.250000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.250000;,
  0.500000;-0.000000;,
  1.000000;0.250000;,
  1.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  -0.000000;0.750000;,
  -0.000000;0.750000;,
  0.500000;0.750000;,
  1.000000;0.500000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;1.000000;;
 }
}