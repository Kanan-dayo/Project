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
 280;
 0.47614;-8.85685;2.12247;,
 -0.48207;-8.76719;2.51942;,
 -0.26754;-11.68199;1.94305;,
 0.10822;-11.71152;1.52256;,
 0.68862;-9.05713;1.28450;,
 0.47614;-8.85685;2.12247;,
 0.10822;-11.71152;1.52256;,
 0.45452;-11.72514;0.76995;,
 0.23568;-8.94938;0.28440;,
 0.68862;-9.05713;1.28450;,
 0.45452;-11.72514;0.76995;,
 -0.00818;-11.69802;-0.02413;,
 -0.40308;-8.90910;-0.37815;,
 0.23568;-8.94938;0.28440;,
 -0.00818;-11.69802;-0.02413;,
 -0.56301;-11.66599;-0.31062;,
 -1.02282;-8.89636;-0.21995;,
 -0.40308;-8.90910;-0.37815;,
 -0.56301;-11.66599;-0.31062;,
 -1.02688;-11.67766;0.11075;,
 -1.59314;-8.71971;0.50703;,
 -1.02282;-8.89636;-0.21995;,
 -1.02688;-11.67766;0.11075;,
 -1.39062;-11.72514;0.70951;,
 -1.40041;-8.74015;2.11517;,
 -1.59314;-8.71971;0.50703;,
 -1.39062;-11.72514;0.70951;,
 -0.82058;-11.74877;1.74277;,
 -0.48207;-8.76719;2.51942;,
 -1.40041;-8.74015;2.11517;,
 -0.82058;-11.74877;1.74277;,
 -0.26754;-11.68199;1.94305;,
 -0.08213;-14.86842;-5.02588;,
 0.37716;-15.60804;-5.11545;,
 -0.23357;-15.68595;-6.58020;,
 -0.33328;-14.90874;-6.36919;,
 0.30139;-16.16084;-4.94593;,
 -0.29746;-16.25135;-6.32079;,
 -3.13162;-16.19991;-3.62686;,
 -3.01737;-15.66888;-3.52491;,
 -3.00867;-15.70699;-5.19924;,
 -2.89787;-16.22607;-5.04814;,
 -2.62295;-15.11072;-3.68879;,
 -2.88700;-15.05059;-5.08551;,
 -1.72884;-13.29901;1.11366;,
 -1.80130;-14.71316;1.19996;,
 -1.19682;-14.55902;2.61239;,
 -0.98389;-13.20665;2.26054;,
 -1.52676;-16.07937;1.16246;,
 -1.12512;-16.04170;2.51888;,
 -1.97453;-13.61439;-0.56163;,
 -2.38433;-14.84825;-0.36175;,
 -2.07761;-16.05386;-0.33119;,
 0.84060;-13.23704;0.76125;,
 1.04636;-14.76195;0.76401;,
 1.06912;-14.54201;-0.97386;,
 0.63162;-13.24183;-1.02716;,
 0.77846;-16.11649;0.80669;,
 0.79258;-15.51967;-0.83805;,
 0.45396;-13.21908;2.05209;,
 0.94235;-14.57825;2.28918;,
 0.81039;-16.03971;2.22878;,
 0.30139;-16.16084;-4.94593;,
 -1.43332;-16.31307;-4.39565;,
 -1.79684;-16.27431;-5.88432;,
 -0.29746;-16.25135;-6.32079;,
 -3.13162;-16.19991;-3.62686;,
 -2.89787;-16.22607;-5.04814;,
 0.77846;-16.11649;0.80669;,
 -0.35352;-16.23901;1.10664;,
 -0.63679;-16.19260;-0.54859;,
 0.79258;-15.51967;-0.83805;,
 -1.52676;-16.07937;1.16246;,
 -2.07761;-16.05386;-0.33119;,
 0.81039;-16.03971;2.22878;,
 -0.10733;-16.09196;2.68410;,
 -1.12512;-16.04170;2.51888;,
 0.94235;-14.57825;2.28918;,
 -0.03680;-14.53773;3.00592;,
 -0.10733;-16.09196;2.68410;,
 0.81039;-16.03971;2.22878;,
 -1.19682;-14.55902;2.61239;,
 -1.12512;-16.04170;2.51888;,
 0.45396;-13.21908;2.05209;,
 -0.11526;-13.18007;2.65816;,
 -0.98389;-13.20665;2.26054;,
 -3.00867;-15.70699;-5.19924;,
 -1.89303;-15.71633;-6.30136;,
 -1.79684;-16.27431;-5.88432;,
 -2.89787;-16.22607;-5.04814;,
 -0.23357;-15.68595;-6.58020;,
 -2.88700;-15.05059;-5.08551;,
 -1.81273;-14.89070;-5.93696;,
 -0.33328;-14.90874;-6.36919;,
 -3.01737;-15.66888;-3.52491;,
 -2.88057;-15.44627;-1.92646;,
 -2.47489;-14.64991;-2.12201;,
 -3.13162;-16.19991;-3.62686;,
 -2.71638;-16.14907;-1.96978;,
 0.90320;-14.90763;-3.05035;,
 0.44019;-13.91095;-3.03522;,
 0.37716;-15.60804;-5.11545;,
 0.57996;-15.68979;-2.89423;,
 -1.02115;-16.26490;-2.47633;,
 0.57996;-15.68979;-2.89423;,
 -1.43332;-16.31307;-4.39565;,
 -2.71638;-16.14907;-1.96978;,
 0.58238;-11.69363;0.77287;,
 0.07732;-11.64233;-0.10013;,
 0.45452;-11.72514;0.76995;,
 0.84060;-13.23704;0.76125;,
 0.63162;-13.24183;-1.02716;,
 -1.13332;-11.62275;0.05347;,
 -1.51404;-11.68770;0.73292;,
 -1.02688;-11.67766;0.11075;,
 -1.97453;-13.61439;-0.56163;,
 -1.72884;-13.29901;1.11366;,
 -1.51404;-11.68770;0.73292;,
 -0.90692;-11.71445;1.83834;,
 -1.39062;-11.72514;0.70951;,
 -1.72884;-13.29901;1.11366;,
 -0.98389;-13.20665;2.26054;,
 -0.90692;-11.71445;1.83834;,
 -0.24441;-11.64118;2.04669;,
 -0.82058;-11.74877;1.74277;,
 -0.98389;-13.20665;2.26054;,
 -0.11526;-13.18007;2.65816;,
 -0.24441;-11.64118;2.04669;,
 0.22317;-11.67773;1.58949;,
 -0.26754;-11.68199;1.94305;,
 -0.11526;-13.18007;2.65816;,
 0.45396;-13.21908;2.05209;,
 0.22317;-11.67773;1.58949;,
 0.58238;-11.69363;0.77287;,
 0.10822;-11.71152;1.52256;,
 0.45396;-13.21908;2.05209;,
 0.84060;-13.23704;0.76125;,
 -0.72175;-14.43511;-4.27104;,
 -0.08213;-14.86842;-5.02588;,
 -0.33328;-14.90874;-6.36919;,
 -0.95995;-14.90110;-6.18611;,
 -1.81273;-14.89070;-5.93696;,
 -1.47042;-14.45310;-4.50370;,
 -0.50201;-13.90095;-2.86571;,
 0.44019;-13.91095;-3.03522;,
 -0.72175;-14.43511;-4.27104;,
 -1.47042;-14.45310;-4.50370;,
 -1.07261;-13.89489;-2.76306;,
 -0.30893;-13.09627;-1.19483;,
 -0.72532;-13.03183;-1.26906;,
 -0.33495;-11.61405;-0.29448;,
 -0.58290;-11.59705;-0.41137;,
 -0.30625;-11.68081;-0.17804;,
 -0.00818;-11.69802;-0.02413;,
 0.07732;-11.64233;-0.10013;,
 -0.30893;-13.09627;-1.19483;,
 -0.72532;-13.03183;-1.26906;,
 0.63162;-13.24183;-1.02716;,
 -1.90831;-14.51807;-3.67983;,
 -2.24468;-14.95499;-5.59461;,
 -2.88700;-15.05059;-5.08551;,
 -2.62295;-15.11072;-3.68879;,
 -1.48504;-14.11695;-2.57452;,
 -1.90831;-14.51807;-3.67983;,
 -2.62295;-15.11072;-3.68879;,
 -2.47489;-14.64991;-2.12201;,
 -1.08352;-13.19888;-1.06620;,
 -1.97453;-13.61439;-0.56163;,
 -0.81040;-11.60767;-0.21924;,
 -1.13332;-11.62275;0.05347;,
 -0.78652;-11.67161;-0.10759;,
 -0.56301;-11.66599;-0.31062;,
 -0.58290;-11.59705;-0.41137;,
 -1.08352;-13.19888;-1.06620;,
 -1.97453;-13.61439;-0.56163;,
 -0.72532;-13.03183;-1.26906;,
 -1.50547;0.83570;1.90343;,
 0.38196;0.58373;2.74209;,
 0.37605;0.48835;1.76942;,
 -0.78544;0.61768;1.22751;,
 -1.37799;-0.50018;1.88245;,
 0.32268;-0.63640;2.70377;,
 -2.30947;0.58366;-0.06523;,
 -1.50547;0.83570;1.90343;,
 -0.78544;0.61768;1.22751;,
 -1.29649;0.44872;-0.10430;,
 -2.51880;-0.85620;0.32090;,
 -1.37799;-0.50018;1.88245;,
 -1.75991;-0.73666;-1.87854;,
 -2.30947;0.58366;-0.06523;,
 -1.29649;0.44872;-0.10430;,
 -1.00143;-0.60910;-1.25880;,
 -1.50342;-1.88002;-1.41951;,
 -2.51880;-0.85620;0.32090;,
 0.10402;-1.36033;-2.62053;,
 -1.75991;-0.73666;-1.87854;,
 -1.00143;-0.60910;-1.25880;,
 0.11875;-0.98668;-1.71716;,
 0.27378;-2.45504;-2.04158;,
 -1.50342;-1.88002;-1.41951;,
 2.00458;-1.39611;-1.80022;,
 0.10402;-1.36033;-2.62053;,
 0.11875;-0.98668;-1.71716;,
 1.29808;-0.95554;-1.23267;,
 1.85851;-2.41607;-1.24322;,
 0.27378;-2.45504;-2.04158;,
 2.91847;-0.47019;-0.00167;,
 2.00458;-1.39611;-1.80022;,
 1.29808;-0.95554;-1.23267;,
 1.94630;-0.15071;-0.07958;,
 2.58029;-1.81183;0.43167;,
 1.85851;-2.41607;-1.24322;,
 2.22997;0.08113;1.94264;,
 2.91847;-0.47019;-0.00167;,
 1.94630;-0.15071;-0.07958;,
 1.50757;0.19383;1.24500;,
 1.98706;-1.19599;1.98365;,
 2.58029;-1.81183;0.43167;,
 0.38196;0.58373;2.74209;,
 2.22997;0.08113;1.94264;,
 1.50757;0.19383;1.24500;,
 0.37605;0.48835;1.76942;,
 0.32268;-0.63640;2.70377;,
 1.98706;-1.19599;1.98365;,
 1.98706;-1.19599;1.98365;,
 -0.43048;-4.48095;4.26241;,
 1.58068;-4.80324;3.63393;,
 2.58029;-1.81183;0.43167;,
 1.58068;-4.80324;3.63393;,
 2.44473;-5.14898;1.51653;,
 1.85851;-2.41607;-1.24322;,
 2.44473;-5.14898;1.51653;,
 1.64335;-5.41671;-0.32703;,
 0.27378;-2.45504;-2.04158;,
 1.64335;-5.41671;-0.32703;,
 0.04019;-5.38782;-1.48095;,
 -1.50342;-1.88002;-1.41951;,
 0.04019;-5.38782;-1.48095;,
 -1.53446;-5.21581;-1.07068;,
 -2.51880;-0.85620;0.32090;,
 -1.53446;-5.21581;-1.07068;,
 -2.79978;-4.89701;0.58695;,
 -1.37799;-0.50018;1.88245;,
 -2.79978;-4.89701;0.58695;,
 -2.42947;-4.56123;2.94846;,
 0.32268;-0.63640;2.70377;,
 -2.42947;-4.56123;2.94846;,
 -0.43048;-4.48095;4.26241;,
 -0.43048;-4.48095;4.26241;,
 -2.42947;-4.56123;2.94846;,
 -1.40041;-8.74015;2.11517;,
 -0.48207;-8.76719;2.51942;,
 -2.42947;-4.56123;2.94846;,
 -2.79978;-4.89701;0.58695;,
 -1.59314;-8.71971;0.50703;,
 -1.40041;-8.74015;2.11517;,
 -2.79978;-4.89701;0.58695;,
 -1.53446;-5.21581;-1.07068;,
 -1.02282;-8.89636;-0.21995;,
 -1.59314;-8.71971;0.50703;,
 -1.53446;-5.21581;-1.07068;,
 0.04019;-5.38782;-1.48095;,
 -0.40308;-8.90910;-0.37815;,
 -1.02282;-8.89636;-0.21995;,
 0.04019;-5.38782;-1.48095;,
 1.64335;-5.41671;-0.32703;,
 0.23568;-8.94938;0.28440;,
 -0.40308;-8.90910;-0.37815;,
 1.64335;-5.41671;-0.32703;,
 2.44473;-5.14898;1.51653;,
 0.68862;-9.05713;1.28450;,
 0.23568;-8.94938;0.28440;,
 2.44473;-5.14898;1.51653;,
 1.58068;-4.80324;3.63393;,
 0.47614;-8.85685;2.12247;,
 0.68862;-9.05713;1.28450;,
 1.58068;-4.80324;3.63393;,
 -0.43048;-4.48095;4.26241;,
 -0.48207;-8.76719;2.51942;,
 0.47614;-8.85685;2.12247;;
 
 110;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;33,36,37,34;,
 4;38,39,40,41;,
 4;39,42,43,40;,
 4;44,45,46,47;,
 4;45,48,49,46;,
 4;50,51,45,44;,
 4;51,52,48,45;,
 4;53,54,55,56;,
 4;54,57,58,55;,
 4;59,60,54,53;,
 4;60,61,57,54;,
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
 4;87,90,65,88;,
 4;91,92,87,86;,
 4;92,93,90,87;,
 4;94,95,96,42;,
 4;95,51,50,96;,
 4;97,98,95,94;,
 4;98,52,51,95;,
 4;55,99,100,56;,
 4;99,101,32,100;,
 4;58,102,99,55;,
 4;102,62,101,99;,
 4;70,103,104,71;,
 4;103,105,62,104;,
 4;73,106,103,70;,
 4;106,97,105,103;,
 4;107,108,14,109;,
 4;110,111,108,107;,
 4;112,113,26,114;,
 4;115,116,113,112;,
 4;117,118,30,119;,
 4;120,121,118,117;,
 4;122,123,2,124;,
 4;125,126,123,122;,
 4;127,128,6,129;,
 4;130,131,128,127;,
 4;132,133,10,134;,
 4;135,136,133,132;,
 4;137,138,139,140;,
 4;137,140,141,142;,
 4;143,144,138,145;,
 4;143,145,146,147;,
 4;148,56,144,143;,
 4;148,143,147,149;,
 4;150,151,18,152;,
 4;150,152,153,154;,
 4;155,156,151,150;,
 4;155,150,154,157;,
 4;158,142,141,159;,
 4;158,159,160,161;,
 4;162,147,146,163;,
 4;162,163,164,165;,
 4;166,149,147,162;,
 4;166,162,165,167;,
 4;168,169,22,170;,
 4;168,170,171,172;,
 4;173,174,169,168;,
 4;173,168,172,175;,
 4;176,177,178,179;,
 4;176,180,181,177;,
 4;182,183,184,185;,
 4;182,186,187,183;,
 4;188,189,190,191;,
 4;188,192,193,189;,
 4;194,195,196,197;,
 4;194,198,199,195;,
 4;200,201,202,203;,
 4;200,204,205,201;,
 4;206,207,208,209;,
 4;206,210,211,207;,
 4;212,213,214,215;,
 4;212,216,217,213;,
 4;218,219,220,221;,
 4;218,222,223,219;,
 4;224,222,225,226;,
 4;227,216,228,229;,
 4;230,210,231,232;,
 4;233,204,234,235;,
 4;236,198,237,238;,
 4;239,192,240,241;,
 4;242,186,243,244;,
 4;245,180,246,247;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;256,257,258,259;,
 4;260,261,262,263;,
 4;264,265,266,267;,
 4;268,269,270,271;,
 4;272,273,274,275;,
 4;276,277,278,279;;
 
 MeshMaterialList {
  12;
  110;
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
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
  5,
  5,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
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
  5,
  6,
  5,
  6,
  6,
  5,
  6,
  6,
  6,
  5,
  6,
  5,
  6,
  6,
  6,
  6,
  5,
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
  6;;
  Material {
   0.512000;0.512000;0.512000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.081600;0.235200;0.081600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.420000;0.310400;0.181600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.172800;0.172800;0.172800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.762400;0.511200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.596000;0.800000;0.775200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.310400;0.220000;0.078400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.661600;0.749600;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.668000;0.643200;0.078400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.266400;0.545600;0.800000;1.000000;;
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
 }
 MeshNormals {
  146;
  0.149403;0.978104;-0.144883;,
  0.196908;0.975364;-0.099461;,
  0.156152;0.905969;-0.393493;,
  0.266212;0.887363;-0.376455;,
  0.266152;0.956853;-0.116595;,
  0.188463;0.846904;-0.497227;,
  0.160771;0.905730;-0.392182;,
  0.167136;0.856398;-0.488516;,
  0.772447;-0.192290;0.605269;,
  0.993278;-0.098976;-0.060028;,
  0.762122;-0.014166;-0.647279;,
  0.596558;-0.017382;-0.802382;,
  -0.665649;-0.067526;-0.743203;,
  -0.981072;-0.125335;-0.147610;,
  -0.718127;-0.188607;0.669867;,
  0.112192;-0.222279;0.968507;,
  -0.211819;0.958428;-0.191177;,
  -0.268979;0.961798;0.050936;,
  -0.246735;0.901393;0.355826;,
  0.070804;0.850628;0.520978;,
  0.312521;0.892850;0.324268;,
  0.298271;0.951473;0.075723;,
  0.136876;0.961283;-0.239166;,
  -0.094004;0.946658;-0.308225;,
  -0.660100;-0.145879;0.736877;,
  -0.998777;-0.011115;0.048175;,
  0.933964;-0.269707;-0.234454;,
  0.852694;-0.163096;0.496299;,
  -0.646278;0.241148;0.723998;,
  -0.739045;0.673194;-0.024940;,
  0.525453;0.776869;-0.346949;,
  0.834151;0.265327;0.483521;,
  -0.908270;-0.217389;0.357474;,
  0.838091;-0.544598;-0.031873;,
  -0.862890;0.471453;-0.182079;,
  0.853899;0.376490;-0.359321;,
  0.588495;0.770540;-0.244830;,
  -0.771457;0.590521;-0.236935;,
  0.895557;-0.251789;-0.366852;,
  -0.876453;-0.238529;-0.418252;,
  -0.922890;-0.170863;0.345078;,
  0.981761;-0.190070;-0.004345;,
  -0.935792;0.232121;0.265355;,
  0.969723;0.241175;0.038370;,
  -0.974234;0.222278;0.038229;,
  -0.671310;0.042624;0.739950;,
  0.948495;0.082663;-0.305818;,
  0.869580;0.067126;0.489209;,
  -0.962197;0.044363;0.268718;,
  0.997035;0.005148;-0.076774;,
  0.936610;0.070008;-0.343309;,
  -0.933767;0.250909;-0.255196;,
  -0.937492;0.005158;0.347969;,
  0.999281;0.025418;0.028137;,
  0.045660;-0.998540;0.028858;,
  0.004672;-0.997184;0.074854;,
  -0.213690;0.948290;-0.234698;,
  0.668873;0.291414;0.683876;,
  0.110405;-0.993438;-0.029862;,
  -0.214168;0.734376;-0.644069;,
  -0.348613;0.724753;-0.594308;,
  -0.070785;-0.944994;-0.319336;,
  0.031207;-0.999486;-0.007320;,
  0.162102;0.074781;0.983936;,
  -0.456355;-0.091756;-0.885054;,
  -0.951911;-0.132934;0.276033;,
  0.708952;-0.705028;-0.017931;,
  -0.754544;0.647489;-0.106875;,
  0.669405;0.654024;-0.352349;,
  -0.972109;0.171526;0.159947;,
  0.980379;0.055684;-0.189094;,
  0.128702;-0.990618;0.045949;,
  -0.251087;0.908700;-0.333497;,
  -0.203282;0.830216;0.519055;,
  0.044055;0.956736;-0.287603;,
  0.201277;0.735731;-0.646674;,
  0.076263;0.975726;-0.205285;,
  0.039974;0.917044;-0.396778;,
  0.328680;0.850335;0.410974;,
  -0.471717;0.873910;-0.117325;,
  -0.586030;0.630182;-0.509352;,
  -0.411875;0.906596;-0.091884;,
  -0.542731;0.806770;-0.233591;,
  -0.025399;0.172712;0.984645;,
  -0.716820;0.173322;0.675373;,
  -0.998906;0.039965;-0.024287;,
  -0.679879;-0.197586;-0.706204;,
  0.037495;-0.348667;-0.936496;,
  0.726756;-0.307927;-0.614009;,
  0.989297;-0.144156;0.022576;,
  0.721944;0.055028;0.689759;,
  0.702127;-0.114695;0.702754;,
  0.970952;-0.239229;-0.004594;,
  0.749277;-0.295954;-0.592449;,
  0.150310;-0.268854;-0.951380;,
  -0.581966;-0.168809;-0.795499;,
  -0.979567;-0.091463;-0.179116;,
  -0.792358;0.002760;0.610050;,
  -0.069308;0.001565;0.997594;,
  0.004254;-0.299211;0.954178;,
  -0.749354;-0.256156;0.610617;,
  -0.960749;-0.205815;-0.186013;,
  -0.615086;-0.163861;-0.771245;,
  0.350246;-0.228048;-0.908472;,
  0.765660;-0.197497;-0.612177;,
  0.964119;-0.263399;-0.033083;,
  0.698620;-0.308926;0.645364;,
  -0.472246;-0.049590;-0.880071;,
  0.146790;-0.988413;0.038635;,
  0.051171;-0.998688;-0.001827;,
  -0.055415;-0.998286;0.018834;,
  -0.058215;-0.998301;-0.002445;,
  0.169450;-0.983681;-0.060489;,
  0.227685;-0.956180;-0.184063;,
  -0.106486;-0.993271;0.045535;,
  -0.090406;-0.995261;0.035803;,
  0.107925;-0.992080;0.064259;,
  -0.098631;-0.991518;0.084640;,
  0.150774;-0.145772;0.977762;,
  -0.361309;0.272824;0.891641;,
  -0.589533;-0.446195;-0.673321;,
  -0.214716;-0.099859;-0.971558;,
  -0.180593;-0.507988;-0.842220;,
  -0.209232;0.326690;-0.921681;,
  -0.059556;-0.996835;0.052656;,
  0.671653;0.430339;-0.603067;,
  0.970173;0.241866;0.016257;,
  -0.941340;0.282530;0.184544;,
  -0.802606;0.411570;-0.431779;,
  -0.632313;0.262869;0.728753;,
  -0.360341;0.291270;0.886180;,
  0.824293;0.252482;0.506748;,
  0.690444;0.307827;0.654622;,
  0.011091;0.916768;-0.399266;,
  0.067701;0.922225;-0.380681;,
  -0.153908;0.529080;-0.834498;,
  0.315208;0.500038;-0.806601;,
  -0.588162;0.456314;-0.667715;,
  -0.688111;0.028674;0.725039;,
  -0.021066;-0.041513;0.998916;,
  -0.996620;-0.031420;0.075909;,
  -0.737607;-0.316083;-0.596680;,
  -0.031271;-0.484916;-0.874002;,
  0.695428;-0.401192;-0.596176;,
  0.971143;-0.233638;0.047894;,
  0.703170;-0.096723;0.704413;;
  110;
  4;106,99,15,8;,
  4;105,106,8,9;,
  4;104,105,9,10;,
  4;103,104,10,11;,
  4;102,107,107,12;,
  4;101,102,12,13;,
  4;100,101,13,14;,
  4;99,100,14,15;,
  4;30,46,50,36;,
  4;46,26,38,50;,
  4;25,44,51,39;,
  4;44,29,37,51;,
  4;42,52,45,28;,
  4;52,40,24,45;,
  4;34,48,52,42;,
  4;48,32,40,52;,
  4;43,53,49,35;,
  4;53,41,33,49;,
  4;31,47,53,43;,
  4;47,27,41,53;,
  4;108,54,61,109;,
  4;54,110,111,61;,
  4;112,62,58,113;,
  4;62,114,115,58;,
  4;116,55,62,112;,
  4;55,117,114,62;,
  4;47,63,118,27;,
  4;63,45,24,118;,
  4;31,57,63,47;,
  4;119,28,45,63;,
  4;120,64,120,39;,
  4;64,121,122,61;,
  4;37,60,64,51;,
  4;60,123,121,64;,
  4;44,69,67,29;,
  4;69,48,34,67;,
  4;25,65,69,44;,
  4;65,32,48,69;,
  4;49,70,68,35;,
  4;70,46,30,68;,
  4;33,66,70,49;,
  4;66,26,46,70;,
  4;58,71,66,33;,
  4;71,54,108,66;,
  4;115,124,71,58;,
  4;124,110,54,71;,
  4;17,18,18,17;,
  4;43,35,125,126;,
  4;20,21,21,20;,
  4;34,42,127,128;,
  4;21,22,22,21;,
  4;42,28,129,127;,
  4;22,23,23,22;,
  4;28,119,130,129;,
  4;23,16,16,23;,
  4;57,31,131,132;,
  4;16,17,17,16;,
  4;31,43,126,131;,
  4;74,30,36,76;,
  4;74,76,60,56;,
  4;77,133,30,74;,
  4;77,74,56,72;,
  4;75,134,68,77;,
  4;75,77,72,59;,
  4;73,19,19,73;,
  4;73,73,18,18;,
  4;75,59,135,136;,
  4;75,136,125,35;,
  4;79,56,60,81;,
  4;79,81,37,29;,
  4;82,72,56,79;,
  4;82,79,29,67;,
  4;80,59,72,82;,
  4;80,82,67,34;,
  4;78,20,20,78;,
  4;78,78,19,19;,
  4;80,34,128,137;,
  4;80,137,135,59;,
  4;0,1,1,0;,
  4;138,84,83,139;,
  4;2,0,0,2;,
  4;140,85,84,138;,
  4;7,2,2,7;,
  4;141,86,85,140;,
  4;6,7,7,6;,
  4;142,87,86,141;,
  4;5,6,6,5;,
  4;143,88,87,142;,
  4;3,5,5,3;,
  4;144,89,88,143;,
  4;4,3,3,4;,
  4;145,90,89,144;,
  4;1,4,4,1;,
  4;139,83,90,145;,
  4;90,83,98,91;,
  4;89,90,91,92;,
  4;88,89,92,93;,
  4;87,88,93,94;,
  4;86,87,94,95;,
  4;85,86,95,96;,
  4;84,85,96,97;,
  4;83,84,97,98;,
  4;98,97,100,99;,
  4;97,96,101,100;,
  4;96,95,102,101;,
  4;95,94,103,102;,
  4;94,93,104,103;,
  4;93,92,105,104;,
  4;92,91,106,105;,
  4;91,98,99,106;;
 }
 MeshTextureCoords {
  280;
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
  0.000000;0.000000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  -0.000000;0.750000;,
  0.500000;0.750000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
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
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;-0.000000;,
  0.000000;0.000000;,
  1.000000;0.500000;,
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
  0.500000;0.250000;,
  0.000000;0.250000;,
  0.500000;-0.000000;,
  1.000000;0.250000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.884820;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.894100;0.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.688590;,
  0.750000;1.000000;,
  1.000000;0.769640;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  0.500000;0.653430;,
  0.500000;0.500000;,
  0.624440;1.000000;,
  1.000000;1.000000;,
  0.537230;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.693150;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.655020;1.000000;,
  0.649480;0.000000;,
  0.500000;-0.000000;,
  0.500000;1.000000;,
  0.750000;0.352940;,
  1.000000;0.310030;,
  1.000000;0.000000;,
  0.750000;0.000000;,
  0.500000;0.356630;,
  0.500000;-0.000000;,
  0.413320;1.000000;,
  1.000000;1.000000;,
  0.481840;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.286750;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  -0.000000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  -0.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
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
  1.000000;0.750000;;
 }
}
