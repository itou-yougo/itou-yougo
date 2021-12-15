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
 96;
 -2.16150;0.45310;2.08830;,
 -2.01170;-0.86500;1.89650;,
 0.00000;0.45310;2.29220;,
 0.00000;-0.96320;2.08830;,
 -3.96450;0.45310;1.47980;,
 -3.69170;-0.76680;1.32690;,
 -3.13880;-1.60350;1.01710;,
 -1.86190;-1.96580;1.32690;,
 0.00000;-2.14460;1.47980;,
 3.96450;0.45310;1.47980;,
 2.16150;0.45310;2.08830;,
 3.69170;-0.76680;1.32690;,
 2.01170;-0.86500;1.89650;,
 1.86190;-1.96580;1.32690;,
 3.13880;-1.60350;1.01710;,
 3.67440;-2.44540;-4.64330;,
 1.98910;-3.12420;-4.56300;,
 3.11140;-2.56730;-6.81810;,
 1.66700;-3.16780;-6.65740;,
 -0.00110;-3.35080;-4.48260;,
 -0.00220;-3.36860;-6.49660;,
 -0.00310;-3.23890;-7.87610;,
 1.05590;-3.10070;-8.47620;,
 2.29960;-2.54950;-8.74150;,
 -3.67680;-2.44540;-4.64330;,
 -3.11630;-2.56730;-6.81810;,
 -1.99140;-3.12420;-4.56300;,
 -1.67160;-3.16780;-6.65740;,
 -2.30700;-2.54950;-8.74150;,
 -1.06280;-3.10070;-8.47620;,
 1.21530;-2.20330;-9.98280;,
 -0.00430;-2.79470;-9.59700;,
 -0.00490;-1.54850;-10.43290;,
 -1.22440;-2.20330;-9.98280;,
 -2.31560;-1.28020;-9.59700;,
 -3.27780;-1.64930;-8.47620;,
 -4.75220;-1.31530;-4.56300;,
 -4.11130;-1.56920;-6.65740;,
 -5.13730;0.01460;-4.48260;,
 -4.49640;-0.42390;-6.49660;,
 -3.74110;-0.78960;-7.87610;,
 4.10670;-1.56920;-6.65740;,
 4.74990;-1.31530;-4.56300;,
 3.27090;-1.64930;-8.47620;,
 3.73500;-0.78960;-7.87610;,
 4.49210;-0.42390;-6.49660;,
 5.13520;0.01460;-4.48260;,
 -5.13670;-1.16290;-2.61560;,
 -5.52190;0.27770;-2.58340;,
 -4.01320;-2.37220;-2.64770;,
 -4.04490;-2.24620;-0.95740;,
 -5.15780;-1.03770;-0.92840;,
 -5.53230;0.40930;-0.89940;,
 -4.70820;-0.86500;0.38550;,
 -5.05060;0.45310;0.46940;,
 -3.69170;-1.96580;0.30160;,
 -2.18340;-3.09800;-2.61560;,
 -0.00040;-3.34010;-2.58340;,
 -2.20440;-2.97280;-0.92840;,
 -0.00010;-3.21560;-0.89940;,
 2.18240;-3.09800;-2.61560;,
 4.01220;-2.37220;-2.64770;,
 2.20420;-2.97280;-0.92840;,
 4.04470;-2.24620;-0.95740;,
 2.01170;-2.63190;0.38550;,
 0.00000;-2.85630;0.46940;,
 3.69170;-1.96580;0.30160;,
 -2.01170;-2.63190;0.38550;,
 5.13580;-1.16290;-2.61560;,
 5.52100;0.27770;-2.58340;,
 5.15750;-1.03770;-0.92840;,
 5.53210;0.40930;-0.89940;,
 4.70820;-0.86500;0.38550;,
 5.05060;0.45310;0.46940;,
 2.33830;-1.30370;-9.55310;,
 1.96690;-1.56790;-9.71720;,
 -0.00490;-1.54850;-10.43290;,
 -2.31560;-1.28020;-9.59700;,
 2.33830;-1.30370;-9.55310;,
 -3.74110;-0.78960;-7.87610;,
 -4.49640;-0.42390;-6.49660;,
 3.73500;-0.78960;-7.87610;,
 4.49210;-0.42390;-6.49660;,
 5.13520;0.01460;-4.48260;,
 -5.13730;0.01460;-4.48260;,
 5.52100;0.27770;-2.58340;,
 -5.52190;0.27770;-2.58340;,
 5.53210;0.40930;-0.89940;,
 5.05060;0.45310;0.46940;,
 3.96450;0.45310;1.47980;,
 2.16150;0.45310;2.08830;,
 0.00000;0.45310;2.29220;,
 -2.16150;0.45310;2.08830;,
 -5.53230;0.40930;-0.89940;,
 -5.05060;0.45310;0.46940;,
 -3.96450;0.45310;1.47980;;
 
 147;
 3;0,1,2;,
 3;2,1,3;,
 3;4,5,0;,
 3;0,5,1;,
 3;5,6,1;,
 3;1,6,7;,
 3;1,7,3;,
 3;3,7,8;,
 3;9,10,11;,
 3;11,10,12;,
 3;10,2,12;,
 3;12,2,3;,
 3;12,3,13;,
 3;13,3,8;,
 3;11,12,14;,
 3;14,12,13;,
 3;15,16,17;,
 3;17,16,18;,
 3;16,19,18;,
 3;18,19,20;,
 3;20,21,18;,
 3;18,21,22;,
 3;17,18,23;,
 3;23,18,22;,
 3;24,25,26;,
 3;26,25,27;,
 3;25,28,27;,
 3;27,28,29;,
 3;29,21,27;,
 3;27,21,20;,
 3;26,27,19;,
 3;19,27,20;,
 3;30,31,32;,
 3;32,31,33;,
 3;23,22,30;,
 3;30,22,31;,
 3;22,21,31;,
 3;31,21,29;,
 3;31,29,33;,
 3;33,29,28;,
 3;33,28,34;,
 3;34,28,35;,
 3;36,37,24;,
 3;24,37,25;,
 3;38,39,36;,
 3;36,39,37;,
 3;39,40,37;,
 3;37,40,35;,
 3;37,35,25;,
 3;25,35,28;,
 3;17,41,15;,
 3;15,41,42;,
 3;23,43,17;,
 3;17,43,41;,
 3;43,44,41;,
 3;41,44,45;,
 3;41,45,42;,
 3;42,45,46;,
 3;36,47,38;,
 3;38,47,48;,
 3;24,49,36;,
 3;36,49,47;,
 3;49,50,47;,
 3;47,50,51;,
 3;47,51,48;,
 3;48,51,52;,
 3;51,53,52;,
 3;52,53,54;,
 3;51,50,53;,
 3;53,50,55;,
 3;53,55,5;,
 3;5,55,6;,
 3;54,53,4;,
 3;4,53,5;,
 3;26,56,24;,
 3;24,56,49;,
 3;19,57,26;,
 3;26,57,56;,
 3;56,57,58;,
 3;58,57,59;,
 3;56,58,49;,
 3;49,58,50;,
 3;19,16,57;,
 3;57,16,60;,
 3;16,15,60;,
 3;60,15,61;,
 3;60,61,62;,
 3;62,61,63;,
 3;57,60,59;,
 3;59,60,62;,
 3;62,64,59;,
 3;59,64,65;,
 3;63,66,62;,
 3;62,66,64;,
 3;66,14,64;,
 3;64,14,13;,
 3;64,13,65;,
 3;65,13,8;,
 3;50,58,55;,
 3;55,58,67;,
 3;58,59,67;,
 3;67,59,65;,
 3;67,65,7;,
 3;7,65,8;,
 3;55,67,6;,
 3;6,67,7;,
 3;15,42,61;,
 3;61,42,68;,
 3;42,46,68;,
 3;68,46,69;,
 3;68,69,70;,
 3;70,69,71;,
 3;61,68,63;,
 3;63,68,70;,
 3;70,72,63;,
 3;63,72,66;,
 3;70,71,72;,
 3;72,71,73;,
 3;73,9,72;,
 3;72,9,11;,
 3;72,11,66;,
 3;66,11,14;,
 3;74,44,43;,
 3;43,23,74;,
 4;23,30,75,74;,
 3;74,75,32;,
 3;32,75,30;,
 3;32,33,34;,
 3;34,35,40;,
 3;76,77,78;,
 3;77,79,78;,
 3;79,80,78;,
 3;78,80,81;,
 3;81,80,82;,
 3;82,80,83;,
 3;80,84,83;,
 3;83,84,85;,
 3;84,86,85;,
 3;85,86,87;,
 3;87,86,88;,
 3;88,86,89;,
 3;89,86,90;,
 3;90,86,91;,
 3;91,86,92;,
 3;86,93,92;,
 3;93,94,92;,
 3;94,95,92;;
 
 MeshMaterialList {
  1;
  147;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "player000.png";
   }
  }
 }
 MeshNormals {
  96;
  0.073847;-0.224270;-0.971725;,
  0.558751;-0.825271;-0.082002;,
  -0.558793;-0.825294;-0.081489;,
  -0.362886;-0.608078;0.706084;,
  0.362886;-0.608078;0.706084;,
  0.000001;-0.999982;0.005939;,
  -0.512942;-0.746055;-0.424608;,
  0.512660;-0.745949;-0.425134;,
  -0.947470;-0.257870;-0.189219;,
  0.947320;-0.257885;-0.189948;,
  -0.611765;-0.768328;0.188190;,
  0.611796;-0.768348;0.188010;,
  -0.552439;-0.217584;0.804654;,
  0.000000;-0.656564;0.754270;,
  0.552439;-0.217584;0.804654;,
  -0.000000;-0.148434;0.988922;,
  -0.000001;-0.990475;-0.137691;,
  -0.858255;-0.135677;-0.494965;,
  0.857369;-0.134764;-0.496747;,
  -0.939549;-0.252913;0.230832;,
  0.016027;-0.983392;0.180785;,
  0.939592;-0.252962;0.230601;,
  -0.856978;-0.486722;-0.169383;,
  -0.917063;-0.257466;-0.304479;,
  0.772274;-0.407062;-0.487743;,
  0.916752;-0.257465;-0.305416;,
  0.856832;-0.486721;-0.170123;,
  -0.965981;-0.254476;-0.046063;,
  -0.563543;-0.826037;-0.009054;,
  -0.889120;-0.431965;0.151230;,
  -0.472395;-0.734220;0.487610;,
  -0.808422;-0.244095;0.535604;,
  -0.015837;-0.999304;0.033775;,
  -0.259002;-0.952205;0.161940;,
  0.563525;-0.826046;-0.009390;,
  0.283220;-0.942705;0.176337;,
  0.472405;-0.734234;0.487580;,
  -0.000000;-0.877132;0.480249;,
  0.965958;-0.254483;-0.046509;,
  0.889157;-0.431987;0.150956;,
  0.808455;-0.244100;0.535551;,
  0.245596;-0.172018;0.953988;,
  -0.245596;-0.172018;0.953988;,
  -0.450210;-0.380113;0.807975;,
  -0.196160;-0.642667;0.740608;,
  0.000000;-0.361700;0.932295;,
  0.196160;-0.642667;0.740608;,
  0.450210;-0.380113;0.807975;,
  0.245764;-0.969194;-0.016253;,
  -0.000000;-0.999098;-0.042471;,
  0.200588;-0.935261;-0.291637;,
  0.551734;-0.816851;-0.168358;,
  -0.551830;-0.816916;-0.167724;,
  -0.200602;-0.935333;-0.291395;,
  -0.245757;-0.969199;-0.016021;,
  0.325596;-0.590279;-0.738619;,
  -0.325878;-0.590381;-0.738413;,
  -0.772854;-0.407612;-0.486364;,
  -0.214916;-0.324790;0.921044;,
  0.214916;-0.324790;0.921044;,
  0.223955;-0.971830;-0.073428;,
  -0.223950;-0.971851;-0.073157;,
  -0.000010;-0.835899;-0.548884;,
  -0.606943;-0.228141;-0.761296;,
  -0.834816;-0.471565;-0.284095;,
  0.834545;-0.471507;-0.284983;,
  0.610258;-0.199335;-0.766714;,
  -0.873133;-0.484127;-0.057101;,
  -0.752741;-0.417816;0.508734;,
  -0.268721;-0.963059;0.017502;,
  0.242578;-0.969762;0.026790;,
  0.234776;-0.866594;0.440336;,
  -0.234775;-0.866588;0.440349;,
  0.873098;-0.484135;-0.057568;,
  0.752779;-0.417836;0.508662;,
  0.450501;-0.123851;-0.884143;,
  0.007541;0.958007;-0.286646;,
  0.007469;0.960675;-0.277576;,
  0.005537;0.961892;-0.273372;,
  0.010221;0.965816;-0.259026;,
  0.001442;0.969750;-0.244095;,
  -0.002919;0.962156;-0.272484;,
  0.000000;0.972104;-0.234552;,
  0.000000;0.982228;-0.187691;,
  0.000000;0.986708;-0.162501;,
  0.000000;0.993073;-0.117497;,
  0.003625;0.998495;-0.054723;,
  -0.003335;0.998418;-0.056131;,
  -0.009664;0.999666;-0.023967;,
  -0.010402;0.999768;-0.018872;,
  -0.005605;0.999583;-0.028311;,
  0.000366;0.999339;-0.036366;,
  0.020467;0.999014;-0.039402;,
  0.039023;0.997515;-0.058651;,
  0.011159;0.999740;-0.019914;,
  0.000000;1.000000;0.000000;;
  147;
  3;42,58,15;,
  3;15,58,45;,
  3;12,43,42;,
  3;42,43,58;,
  3;43,3,58;,
  3;58,3,44;,
  3;58,44,45;,
  3;45,44,13;,
  3;14,41,47;,
  3;47,41,59;,
  3;41,15,59;,
  3;59,15,45;,
  3;59,45,46;,
  3;46,45,13;,
  3;47,59,4;,
  3;4,59,46;,
  3;1,48,51;,
  3;51,48,60;,
  3;48,5,60;,
  3;60,5,49;,
  3;49,16,60;,
  3;60,16,50;,
  3;51,60,7;,
  3;7,60,50;,
  3;2,52,54;,
  3;54,52,61;,
  3;52,6,61;,
  3;61,6,53;,
  3;53,16,61;,
  3;61,16,49;,
  3;54,61,5;,
  3;5,61,49;,
  3;55,62,0;,
  3;0,62,56;,
  3;7,50,55;,
  3;55,50,62;,
  3;50,16,62;,
  3;62,16,53;,
  3;62,53,56;,
  3;56,53,6;,
  3;56,6,63;,
  3;63,6,57;,
  3;22,64,2;,
  3;2,64,52;,
  3;8,23,22;,
  3;22,23,64;,
  3;23,17,64;,
  3;64,17,57;,
  3;64,57,52;,
  3;52,57,6;,
  3;51,65,1;,
  3;1,65,26;,
  3;7,24,51;,
  3;51,24,65;,
  3;24,18,65;,
  3;65,18,25;,
  3;65,25,26;,
  3;26,25,9;,
  3;22,67,8;,
  3;8,67,27;,
  3;2,28,22;,
  3;22,28,67;,
  3;28,10,67;,
  3;67,10,29;,
  3;67,29,27;,
  3;27,29,19;,
  3;29,68,19;,
  3;19,68,31;,
  3;29,10,68;,
  3;68,10,30;,
  3;68,30,43;,
  3;43,30,3;,
  3;31,68,12;,
  3;12,68,43;,
  3;54,69,2;,
  3;2,69,28;,
  3;5,32,54;,
  3;54,32,69;,
  3;69,32,33;,
  3;33,32,20;,
  3;69,33,28;,
  3;28,33,10;,
  3;5,48,32;,
  3;32,48,70;,
  3;48,1,70;,
  3;70,1,34;,
  3;70,34,35;,
  3;35,34,11;,
  3;32,70,20;,
  3;20,70,35;,
  3;35,71,20;,
  3;20,71,37;,
  3;11,36,35;,
  3;35,36,71;,
  3;36,4,71;,
  3;71,4,46;,
  3;71,46,37;,
  3;37,46,13;,
  3;10,33,30;,
  3;30,33,72;,
  3;33,20,72;,
  3;72,20,37;,
  3;72,37,44;,
  3;44,37,13;,
  3;30,72,3;,
  3;3,72,44;,
  3;1,26,34;,
  3;34,26,73;,
  3;26,9,73;,
  3;73,9,38;,
  3;73,38,39;,
  3;39,38,21;,
  3;34,73,11;,
  3;11,73,39;,
  3;39,74,11;,
  3;11,74,36;,
  3;39,21,74;,
  3;74,21,40;,
  3;40,14,74;,
  3;74,14,47;,
  3;74,47,36;,
  3;36,47,4;,
  3;66,18,24;,
  3;24,7,66;,
  4;7,55,75,66;,
  3;66,75,0;,
  3;0,75,55;,
  3;0,56,63;,
  3;63,57,17;,
  3;76,77,78;,
  3;77,79,78;,
  3;79,80,78;,
  3;78,80,81;,
  3;81,80,82;,
  3;82,80,83;,
  3;80,84,83;,
  3;83,84,85;,
  3;84,86,85;,
  3;85,86,87;,
  3;87,86,88;,
  3;88,86,89;,
  3;89,86,90;,
  3;90,86,91;,
  3;91,86,92;,
  3;86,93,92;,
  3;93,94,92;,
  3;94,95,92;;
 }
 MeshTextureCoords {
  96;
  0.914160;0.766860;,
  0.918150;0.775180;,
  0.931360;0.764340;,
  0.931690;0.774390;,
  0.900990;0.775930;,
  0.908050;0.781860;,
  0.913780;0.785710;,
  0.922050;0.785090;,
  0.932320;0.782730;,
  0.959900;0.772300;,
  0.947320;0.766600;,
  0.954690;0.778650;,
  0.944400;0.775140;,
  0.942700;0.782360;,
  0.950200;0.782770;,
  0.955640;0.813990;,
  0.945870;0.814560;,
  0.953390;0.825990;,
  0.945190;0.825570;,
  0.935370;0.815300;,
  0.936580;0.825620;,
  0.937410;0.832470;,
  0.942880;0.834870;,
  0.949620;0.836190;,
  0.915020;0.818740;,
  0.920200;0.830080;,
  0.924890;0.816990;,
  0.928160;0.827650;,
  0.926420;0.839130;,
  0.932680;0.836160;,
  0.944980;0.843140;,
  0.938480;0.841040;,
  0.939510;0.849290;,
  0.932710;0.844720;,
  0.924900;0.847690;,
  0.919400;0.840420;,
  0.905890;0.819740;,
  0.912270;0.831410;,
  0.897130;0.821220;,
  0.904870;0.833180;,
  0.912560;0.840610;,
  0.961250;0.825310;,
  0.964440;0.812820;,
  0.956690;0.835690;,
  0.963300;0.834120;,
  0.968650;0.825150;,
  0.972910;0.812110;,
  0.902370;0.808130;,
  0.892670;0.808600;,
  0.912020;0.807770;,
  0.911090;0.798430;,
  0.901580;0.797890;,
  0.891730;0.796570;,
  0.903100;0.789380;,
  0.894280;0.785880;,
  0.911950;0.791030;,
  0.922760;0.806790;,
  0.934300;0.805460;,
  0.921840;0.797940;,
  0.933460;0.796760;,
  0.945720;0.804270;,
  0.956040;0.802960;,
  0.944870;0.795530;,
  0.954990;0.794030;,
  0.943430;0.788560;,
  0.932820;0.789430;,
  0.952810;0.787350;,
  0.922090;0.790870;,
  0.965050;0.801230;,
  0.974030;0.799480;,
  0.963560;0.791680;,
  0.972120;0.788420;,
  0.960480;0.784340;,
  0.967580;0.779560;,
  0.953340;0.843780;,
  0.950460;0.843710;,
  0.935790;0.742590;,
  0.942540;0.741260;,
  0.929470;0.739410;,
  0.947260;0.737280;,
  0.950110;0.733920;,
  0.925850;0.734410;,
  0.923800;0.730390;,
  0.921920;0.724550;,
  0.953260;0.728740;,
  0.920550;0.718910;,
  0.955830;0.723630;,
  0.920190;0.713820;,
  0.921270;0.709670;,
  0.924180;0.706680;,
  0.929210;0.704970;,
  0.935040;0.704140;,
  0.940540;0.703560;,
  0.958910;0.719350;,
  0.960910;0.714940;,
  0.959310;0.710180;;
 }
}
