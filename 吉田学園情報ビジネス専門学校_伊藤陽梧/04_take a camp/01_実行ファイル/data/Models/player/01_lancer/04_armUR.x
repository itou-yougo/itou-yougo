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
 251;
 -1.72091;0.27408;0.07160;,
 -1.85221;0.23418;0.09720;,
 -1.81081;0.23418;0.14600;,
 -1.69921;0.27408;0.09720;,
 -1.74651;0.23418;0.18470;,
 -1.66531;0.27408;0.11760;,
 -1.66531;0.23418;0.20950;,
 -1.62271;0.27408;0.13060;,
 -1.57541;0.23418;0.21810;,
 -1.57541;0.27408;0.13510;,
 -1.57541;0.27408;-0.04870;,
 -1.57541;0.23418;-0.13170;,
 -1.66531;0.23418;-0.12310;,
 -1.62271;0.27408;-0.04430;,
 -1.74651;0.23418;-0.09830;,
 -1.66531;0.27408;-0.03120;,
 -1.81081;0.23418;-0.05960;,
 -1.69921;0.27408;-0.01090;,
 -1.85221;0.23418;-0.01090;,
 -1.72091;0.27408;0.01480;,
 -1.86641;0.23418;0.04320;,
 -1.72841;0.27408;0.04320;,
 -1.85221;0.23418;0.09720;,
 -1.72091;0.27408;0.07160;,
 -1.95641;0.17218;0.11760;,
 -1.89951;0.17218;0.18470;,
 -1.81081;0.17218;0.23790;,
 -1.69921;0.17218;0.27210;,
 -1.57541;0.17218;0.28390;,
 -1.57541;0.17218;-0.19750;,
 -1.69921;0.17218;-0.18570;,
 -1.81081;0.17218;-0.15150;,
 -1.89951;0.17218;-0.09830;,
 -1.95641;0.17218;-0.03120;,
 -1.97601;0.17218;0.04320;,
 -1.95641;0.17218;0.11760;,
 -2.02321;0.09398;0.13060;,
 -1.95641;0.09398;0.20950;,
 -1.85221;0.09398;0.27210;,
 -1.72091;0.09398;0.31230;,
 -1.57541;0.09398;0.32610;,
 -1.57541;0.09398;-0.23980;,
 -1.72091;0.09398;-0.22590;,
 -1.85221;0.09398;-0.18570;,
 -1.95641;0.09398;-0.12310;,
 -2.02321;0.09398;-0.04430;,
 -2.04631;0.09398;0.04320;,
 -2.02321;0.09398;0.13060;,
 -2.04631;0.00728;0.13510;,
 -1.97601;0.00728;0.21810;,
 -1.86641;0.00728;0.28390;,
 -1.72841;0.00728;0.32610;,
 -1.57541;0.00728;0.34070;,
 -1.57541;0.00728;-0.25430;,
 -1.72841;0.00728;-0.23980;,
 -1.86641;0.00728;-0.19750;,
 -1.97601;0.00728;-0.13170;,
 -2.04631;0.00728;-0.04870;,
 -2.07051;0.00728;0.04320;,
 -2.04631;0.00728;0.13510;,
 -2.02321;-0.07942;0.13060;,
 -1.95641;-0.07942;0.20950;,
 -1.85221;-0.07942;0.27210;,
 -1.72091;-0.07942;0.31230;,
 -1.57541;-0.07942;0.32610;,
 -1.57541;-0.07942;-0.23980;,
 -1.72091;-0.07942;-0.22590;,
 -1.85221;-0.07942;-0.18570;,
 -1.95641;-0.07942;-0.12310;,
 -2.02321;-0.07942;-0.04430;,
 -2.04631;-0.07942;0.04320;,
 -2.02321;-0.07942;0.13060;,
 -1.95641;-0.15762;0.11760;,
 -1.89951;-0.15762;0.18470;,
 -1.81081;-0.15762;0.23790;,
 -1.69921;-0.15762;0.27210;,
 -1.57541;-0.15762;0.28390;,
 -1.57541;-0.15762;-0.19750;,
 -1.69921;-0.15762;-0.18570;,
 -1.81081;-0.15762;-0.15150;,
 -1.89951;-0.15762;-0.09830;,
 -1.95641;-0.15762;-0.03120;,
 -1.97601;-0.15762;0.04320;,
 -1.95641;-0.15762;0.11760;,
 -1.85221;-0.21972;0.09720;,
 -1.81081;-0.21972;0.14600;,
 -1.74651;-0.21972;0.18470;,
 -1.66531;-0.21972;0.20950;,
 -1.57541;-0.21972;0.21810;,
 -1.57541;-0.21972;-0.13170;,
 -1.66531;-0.21972;-0.12310;,
 -1.74651;-0.21972;-0.09830;,
 -1.81081;-0.21972;-0.05960;,
 -1.85221;-0.21972;-0.01090;,
 -1.86641;-0.21972;0.04320;,
 -1.85221;-0.21972;0.09720;,
 -1.72091;-0.25962;0.07160;,
 -1.69921;-0.25962;0.09720;,
 -1.66531;-0.25962;0.11760;,
 -1.62271;-0.25962;0.13060;,
 -1.57541;-0.25962;0.13510;,
 -1.57541;-0.25962;-0.04870;,
 -1.62271;-0.25962;-0.04430;,
 -1.66531;-0.25962;-0.03120;,
 -1.69921;-0.25962;-0.01090;,
 -1.72091;-0.25962;0.01480;,
 -1.72841;-0.25962;0.04320;,
 -1.72091;-0.25962;0.07160;,
 -1.57541;0.28778;0.04320;,
 -1.57541;0.28778;0.04320;,
 -1.57541;0.28778;0.04320;,
 -1.57541;0.28778;0.04320;,
 -1.57541;0.28778;0.04320;,
 -1.57541;0.28778;0.04320;,
 -1.57541;0.28778;0.04320;,
 -1.57541;0.28778;0.04320;,
 -1.57541;0.28778;0.04320;,
 -1.57541;0.28778;0.04320;,
 -1.57541;-0.27332;0.04320;,
 -1.57541;-0.27332;0.04320;,
 -1.57541;-0.27332;0.04320;,
 -1.57541;-0.27332;0.04320;,
 -1.57541;-0.27332;0.04320;,
 -1.57541;-0.27332;0.04320;,
 -1.57541;-0.27332;0.04320;,
 -1.57541;-0.27332;0.04320;,
 -1.57541;-0.27332;0.04320;,
 -1.57541;-0.27332;0.04320;,
 -1.57651;-0.25932;0.13510;,
 -0.33651;-0.33782;0.16060;,
 -0.33651;-0.28692;0.26660;,
 -1.57651;-0.21952;0.21800;,
 -0.33651;-0.20762;0.35070;,
 -1.57651;-0.15742;0.28390;,
 -0.33651;-0.10762;0.40480;,
 -1.57651;-0.07912;0.32620;,
 -0.33651;0.00318;0.42340;,
 -1.57651;0.00758;0.34070;,
 -0.33651;0.11398;0.40480;,
 -1.57651;0.09428;0.32620;,
 -0.33651;0.21398;0.35070;,
 -1.57651;0.17258;0.28390;,
 -0.33651;0.29328;0.26660;,
 -1.57651;0.23468;0.21800;,
 -0.33651;0.34428;0.16060;,
 -1.57651;0.27458;0.13510;,
 -0.33651;0.36178;0.04310;,
 -1.57651;0.28828;0.04310;,
 -0.33651;0.34428;-0.07440;,
 -1.57651;0.27458;-0.04890;,
 -0.33651;0.29328;-0.18040;,
 -1.57651;0.23468;-0.13190;,
 -0.33651;0.21398;-0.26460;,
 -1.57651;0.17258;-0.19770;,
 -0.33651;0.11398;-0.31860;,
 -1.57651;0.09428;-0.24000;,
 -0.33651;0.00318;-0.33720;,
 -1.57651;0.00758;-0.25450;,
 -0.33651;-0.10762;-0.31860;,
 -1.57651;-0.07912;-0.24000;,
 -0.33651;-0.20762;-0.26460;,
 -1.57651;-0.15742;-0.19770;,
 -0.33651;-0.28692;-0.18040;,
 -1.57651;-0.21952;-0.13190;,
 -0.33651;-0.33782;-0.07440;,
 -1.57651;-0.25932;-0.04890;,
 -0.33651;-0.35542;0.04310;,
 -1.57651;-0.27312;0.04310;,
 -0.33651;-0.33782;0.16060;,
 -1.57651;-0.25932;0.13510;,
 -1.57651;-0.21952;0.21800;,
 -1.57651;0.00758;0.04310;,
 -1.57651;-0.25932;0.13510;,
 -1.57651;-0.15742;0.28390;,
 -1.57651;-0.07912;0.32620;,
 -1.57651;0.00758;0.34070;,
 -1.57651;0.09428;0.32620;,
 -1.57651;0.17258;0.28390;,
 -1.57651;0.23468;0.21800;,
 -1.57651;0.27458;0.13510;,
 -1.57651;0.28828;0.04310;,
 -1.57651;0.27458;-0.04890;,
 -1.57651;0.23468;-0.13190;,
 -1.57651;0.17258;-0.19770;,
 -1.57651;0.09428;-0.24000;,
 -1.57651;0.00758;-0.25450;,
 -1.57651;-0.07912;-0.24000;,
 -1.57651;-0.15742;-0.19770;,
 -1.57651;-0.21952;-0.13190;,
 -1.57651;-0.25932;-0.04890;,
 -1.57651;-0.27312;0.04310;,
 -0.33651;-0.33782;0.16060;,
 -0.33651;0.00088;0.04310;,
 -0.33651;-0.28692;0.26660;,
 -0.33651;-0.20762;0.35070;,
 -0.33651;-0.10762;0.40480;,
 -0.33651;0.00318;0.42340;,
 -0.33651;0.11398;0.40480;,
 -0.33651;0.21398;0.35070;,
 -0.33651;0.29328;0.26660;,
 -0.33651;0.34428;0.16060;,
 -0.33651;0.36178;0.04310;,
 -0.33651;0.34428;-0.07440;,
 -0.33651;0.29328;-0.18040;,
 -0.33651;0.21398;-0.26460;,
 -0.33651;0.11398;-0.31860;,
 -0.33651;0.00318;-0.33720;,
 -0.33651;-0.10762;-0.31860;,
 -0.33651;-0.20762;-0.26460;,
 -0.33651;-0.28692;-0.18040;,
 -0.33651;-0.33782;-0.07440;,
 -0.33651;-0.35542;0.04310;,
 -0.10991;0.17998;-0.18610;,
 -0.04121;-0.01622;-0.25480;,
 -0.30611;-0.01622;-0.34310;,
 -0.30611;0.24868;-0.25480;,
 -0.57091;-0.01622;-0.25480;,
 -0.50231;0.17998;-0.18610;,
 -0.30611;-0.28102;-0.25480;,
 -0.50231;-0.21242;-0.18610;,
 -0.10991;-0.21242;-0.18610;,
 -0.04121;-0.28102;0.01010;,
 -0.30611;-0.36932;0.01010;,
 -0.57091;-0.28102;0.01010;,
 -0.30611;-0.28102;0.27490;,
 -0.50231;-0.21242;0.20620;,
 -0.10991;-0.21242;0.20620;,
 -0.04121;-0.01622;0.27490;,
 -0.30611;-0.01622;0.36320;,
 -0.57091;-0.01622;0.27490;,
 -0.30611;0.24868;0.27490;,
 -0.50231;0.17998;0.20620;,
 -0.10991;0.17998;0.20620;,
 -0.04121;0.24868;0.01010;,
 -0.30611;0.33698;0.01010;,
 -0.57091;0.24868;0.01010;,
 -0.30611;0.24868;-0.25480;,
 -0.50231;0.17998;-0.18610;,
 -0.10991;0.17998;-0.18610;,
 -0.65921;-0.01622;0.01010;,
 -0.57091;0.24868;0.01010;,
 -0.57091;-0.01622;0.27490;,
 -0.50231;0.17998;0.20620;,
 -0.57091;-0.28102;0.01010;,
 -0.50231;-0.21242;0.20620;,
 -0.10991;0.17998;0.20620;,
 -0.04121;-0.01622;0.27490;,
 0.04709;-0.01622;0.01010;,
 -0.04121;0.24868;0.01010;,
 -0.04121;-0.28102;0.01010;,
 -0.10991;-0.21242;0.20620;;
 
 184;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;10,11,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;1,24,25,2;,
 4;2,25,26,4;,
 4;4,26,27,6;,
 4;6,27,28,8;,
 4;11,29,30,12;,
 4;12,30,31,14;,
 4;14,31,32,16;,
 4;16,32,33,18;,
 4;18,33,34,20;,
 4;20,34,35,22;,
 4;24,36,37,25;,
 4;25,37,38,26;,
 4;26,38,39,27;,
 4;27,39,40,28;,
 4;29,41,42,30;,
 4;30,42,43,31;,
 4;31,43,44,32;,
 4;32,44,45,33;,
 4;33,45,46,34;,
 4;34,46,47,35;,
 4;36,48,49,37;,
 4;37,49,50,38;,
 4;38,50,51,39;,
 4;39,51,52,40;,
 4;41,53,54,42;,
 4;42,54,55,43;,
 4;43,55,56,44;,
 4;44,56,57,45;,
 4;45,57,58,46;,
 4;46,58,59,47;,
 4;48,60,61,49;,
 4;49,61,62,50;,
 4;50,62,63,51;,
 4;51,63,64,52;,
 4;53,65,66,54;,
 4;54,66,67,55;,
 4;55,67,68,56;,
 4;56,68,69,57;,
 4;57,69,70,58;,
 4;58,70,71,59;,
 4;60,72,73,61;,
 4;61,73,74,62;,
 4;62,74,75,63;,
 4;63,75,76,64;,
 4;65,77,78,66;,
 4;66,78,79,67;,
 4;67,79,80,68;,
 4;68,80,81,69;,
 4;69,81,82,70;,
 4;70,82,83,71;,
 4;72,84,85,73;,
 4;73,85,86,74;,
 4;74,86,87,75;,
 4;75,87,88,76;,
 4;77,89,90,78;,
 4;78,90,91,79;,
 4;79,91,92,80;,
 4;80,92,93,81;,
 4;81,93,94,82;,
 4;82,94,95,83;,
 4;84,96,97,85;,
 4;85,97,98,86;,
 4;86,98,99,87;,
 4;87,99,100,88;,
 4;89,101,102,90;,
 4;90,102,103,91;,
 4;91,103,104,92;,
 4;92,104,105,93;,
 4;93,105,106,94;,
 4;94,106,107,95;,
 3;3,108,0;,
 3;5,109,3;,
 3;7,110,5;,
 3;9,111,7;,
 3;13,112,10;,
 3;15,113,13;,
 3;17,114,15;,
 3;19,115,17;,
 3;21,116,19;,
 3;23,117,21;,
 3;96,118,97;,
 3;97,119,98;,
 3;98,120,99;,
 3;99,121,100;,
 3;101,122,102;,
 3;102,123,103;,
 3;103,124,104;,
 3;104,125,105;,
 3;105,126,106;,
 3;106,127,107;,
 4;128,129,130,131;,
 4;131,130,132,133;,
 4;133,132,134,135;,
 4;135,134,136,137;,
 4;137,136,138,139;,
 4;139,138,140,141;,
 4;141,140,142,143;,
 4;143,142,144,145;,
 4;145,144,146,147;,
 4;147,146,148,149;,
 4;149,148,150,151;,
 4;151,150,152,153;,
 4;153,152,154,155;,
 4;155,154,156,157;,
 4;157,156,158,159;,
 4;159,158,160,161;,
 4;161,160,162,163;,
 4;163,162,164,165;,
 4;165,164,166,167;,
 4;167,166,168,169;,
 3;170,171,172;,
 3;173,171,170;,
 3;174,171,173;,
 3;175,171,174;,
 3;176,171,175;,
 3;177,171,176;,
 3;178,171,177;,
 3;179,171,178;,
 3;180,171,179;,
 3;181,171,180;,
 3;182,171,181;,
 3;183,171,182;,
 3;184,171,183;,
 3;185,171,184;,
 3;186,171,185;,
 3;187,171,186;,
 3;188,171,187;,
 3;189,171,188;,
 3;190,171,189;,
 3;172,171,190;,
 3;191,192,193;,
 3;193,192,194;,
 3;194,192,195;,
 3;195,192,196;,
 3;196,192,197;,
 3;197,192,198;,
 3;198,192,199;,
 3;199,192,200;,
 3;200,192,201;,
 3;201,192,202;,
 3;202,192,203;,
 3;203,192,204;,
 3;204,192,205;,
 3;205,192,206;,
 3;206,192,207;,
 3;207,192,208;,
 3;208,192,209;,
 3;209,192,210;,
 3;210,192,211;,
 3;211,192,191;,
 4;212,213,214,215;,
 4;215,214,216,217;,
 4;214,218,219,216;,
 4;213,220,218,214;,
 4;220,221,222,218;,
 4;218,222,223,219;,
 4;222,224,225,223;,
 4;221,226,224,222;,
 4;226,227,228,224;,
 4;224,228,229,225;,
 4;228,230,231,229;,
 4;227,232,230,228;,
 4;232,233,234,230;,
 4;230,234,235,231;,
 4;234,236,237,235;,
 4;233,238,236,234;,
 4;217,216,239,240;,
 4;240,239,241,242;,
 4;239,243,244,241;,
 4;216,219,243,239;,
 4;245,246,247,248;,
 4;248,247,213,212;,
 4;247,249,220,213;,
 4;246,250,249,247;;
 
 MeshMaterialList {
  1;
  184;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.432000;0.160000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  149;
  -0.174471;0.980156;0.094102;,
  -0.146931;0.973171;0.177057;,
  -0.105338;0.964841;0.240803;,
  -0.054786;0.958322;0.280387;,
  -0.027982;0.955545;0.293513;,
  -0.027604;0.955521;-0.293630;,
  -0.054771;0.958327;-0.280373;,
  -0.105410;0.964812;-0.240889;,
  -0.146869;0.973166;-0.177138;,
  -0.174510;0.980158;-0.094000;,
  -0.184182;0.982892;0.000016;,
  -0.363543;0.910933;0.195035;,
  -0.299184;0.884020;0.359162;,
  -0.209167;0.854069;0.476251;,
  -0.106838;0.832158;0.544149;,
  -0.053957;0.823139;0.565270;,
  -0.053736;0.823083;-0.565373;,
  -0.106842;0.832127;-0.544196;,
  -0.209222;0.854008;-0.476336;,
  -0.299144;0.883967;-0.359328;,
  -0.363574;0.910917;-0.195050;,
  -0.387409;0.921908;0.000044;,
  -0.576623;0.757371;0.306422;,
  -0.455111;0.706091;0.542503;,
  -0.305250;0.655112;0.691123;,
  -0.151746;0.621100;0.768901;,
  -0.075313;0.607668;0.790612;,
  -0.075448;0.607888;-0.790430;,
  -0.151811;0.621204;-0.768803;,
  -0.305250;0.655112;-0.691123;,
  -0.455024;0.706071;-0.542602;,
  -0.576560;0.757394;-0.306484;,
  -0.625645;0.780108;0.000058;,
  -0.787168;0.457703;0.413370;,
  -0.590014;0.406531;0.697578;,
  -0.378356;0.361377;0.852205;,
  -0.183152;0.333860;0.924658;,
  -0.089590;0.323519;0.941971;,
  -0.089742;0.323768;-0.941871;,
  -0.183298;0.334114;-0.924537;,
  -0.378415;0.361499;-0.852127;,
  -0.589924;0.406469;-0.697691;,
  -0.787151;0.457660;-0.413450;,
  -0.875772;0.482725;0.000063;,
  -0.886442;-0.000009;0.462840;,
  -0.647182;-0.000003;0.762335;,
  -0.406503;0.000002;0.913649;,
  -0.194554;0.000002;0.980892;,
  -0.094708;-0.000001;0.995505;,
  -0.094724;-0.000001;-0.995504;,
  -0.194720;-0.000001;-0.980859;,
  -0.406661;-0.000001;-0.913579;,
  -0.647069;-0.000001;-0.762431;,
  -0.886399;-0.000005;-0.462922;,
  -1.000000;-0.000011;0.000066;,
  -0.787171;-0.457699;0.413369;,
  -0.590014;-0.406531;0.697578;,
  -0.378356;-0.361378;0.852204;,
  -0.183152;-0.333862;0.924658;,
  -0.089590;-0.323517;0.941972;,
  -0.089742;-0.323766;-0.941871;,
  -0.183298;-0.334119;-0.924536;,
  -0.378415;-0.361504;-0.852125;,
  -0.589925;-0.406468;-0.697691;,
  -0.787150;-0.457662;-0.413450;,
  -0.875773;-0.482723;0.000064;,
  -0.576873;-0.757129;0.306550;,
  -0.455286;-0.705820;0.542709;,
  -0.305356;-0.654815;0.691358;,
  -0.151794;-0.620796;0.769136;,
  -0.075335;-0.607364;0.790844;,
  -0.075472;-0.607566;-0.790675;,
  -0.151859;-0.620892;-0.769046;,
  -0.305356;-0.654814;-0.691358;,
  -0.455201;-0.705798;-0.542809;,
  -0.576812;-0.757150;-0.306614;,
  -0.625935;-0.779875;0.000057;,
  -0.363828;-0.910787;0.195184;,
  -0.299399;-0.883844;0.359416;,
  -0.209305;-0.853864;0.476559;,
  -0.106902;-0.831942;0.544467;,
  -0.053987;-0.822923;0.565582;,
  -0.053767;-0.822854;-0.565703;,
  -0.106907;-0.831905;-0.544523;,
  -0.209359;-0.853803;-0.476644;,
  -0.299361;-0.883789;-0.359583;,
  -0.363870;-0.910766;-0.195203;,
  -0.387735;-0.921771;0.000042;,
  -0.174468;-0.980156;0.094100;,
  -0.146929;-0.973172;0.177054;,
  -0.105336;-0.964842;0.240799;,
  -0.054785;-0.958324;0.280383;,
  -0.027981;-0.955547;0.293508;,
  -0.027603;-0.955522;-0.293625;,
  -0.054770;-0.958329;-0.280368;,
  -0.105408;-0.964813;-0.240885;,
  -0.146867;-0.973167;-0.177135;,
  -0.174507;-0.980159;-0.093999;,
  -0.184179;-0.982893;0.000016;,
  -0.057896;0.998323;0.000028;,
  -0.057892;-0.998323;0.000028;,
  -0.066402;-0.953755;0.293160;,
  -0.066839;-0.822501;0.564823;,
  -0.067247;-0.607991;0.791091;,
  -0.067263;-0.324074;0.943638;,
  -0.066521;0.000007;0.997785;,
  -0.064970;0.324134;0.943778;,
  -0.062950;0.608169;0.791308;,
  -0.061022;0.822566;0.565386;,
  -0.059667;0.954173;0.293247;,
  -0.059169;0.998248;0.000000;,
  -0.059658;0.954208;-0.293135;,
  -0.061014;0.822610;-0.565324;,
  -0.062971;0.607983;-0.791449;,
  -0.064989;0.323950;-0.943839;,
  -0.066521;0.000007;-0.997785;,
  -0.067281;-0.323891;-0.943699;,
  -0.067272;-0.607804;-0.791232;,
  -0.066836;-0.822544;-0.564761;,
  -0.066392;-0.953790;-0.293049;,
  -0.066234;-0.997804;-0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.577350;0.577350;-0.577350;,
  -0.577465;0.577293;-0.577293;,
  0.577293;-0.577464;-0.577293;,
  -0.577408;-0.577407;-0.577236;,
  0.577253;-0.577424;0.577373;,
  -0.577368;-0.577367;0.577316;,
  0.577310;0.577310;0.577430;,
  -0.577425;0.577253;0.577373;,
  0.707004;-0.707210;0.000079;,
  -0.707155;-0.000031;0.707058;,
  -0.000032;0.707052;0.707162;,
  0.707052;-0.000031;0.707162;,
  -0.707210;0.707003;0.000079;,
  0.707107;0.707107;0.000079;,
  -0.000032;0.707107;-0.707107;,
  -0.707210;-0.000031;-0.707003;,
  -0.000032;-0.707210;-0.707004;,
  0.707107;-0.000031;-0.707107;,
  -0.707107;-0.707106;0.000079;,
  -0.000032;-0.707155;0.707059;,
  -0.000031;-0.000031;-1.000000;,
  -0.000031;-1.000000;0.000078;,
  -0.000031;-0.000031;1.000000;,
  -0.000031;1.000000;0.000078;,
  -1.000000;-0.000031;0.000078;,
  1.000000;-0.000031;0.000078;;
  184;
  4;0,11,12,1;,
  4;1,12,13,2;,
  4;2,13,14,3;,
  4;3,14,15,4;,
  4;5,16,17,6;,
  4;6,17,18,7;,
  4;7,18,19,8;,
  4;8,19,20,9;,
  4;9,20,21,10;,
  4;10,21,11,0;,
  4;11,22,23,12;,
  4;12,23,24,13;,
  4;13,24,25,14;,
  4;14,25,26,15;,
  4;16,27,28,17;,
  4;17,28,29,18;,
  4;18,29,30,19;,
  4;19,30,31,20;,
  4;20,31,32,21;,
  4;21,32,22,11;,
  4;22,33,34,23;,
  4;23,34,35,24;,
  4;24,35,36,25;,
  4;25,36,37,26;,
  4;27,38,39,28;,
  4;28,39,40,29;,
  4;29,40,41,30;,
  4;30,41,42,31;,
  4;31,42,43,32;,
  4;32,43,33,22;,
  4;33,44,45,34;,
  4;34,45,46,35;,
  4;35,46,47,36;,
  4;36,47,48,37;,
  4;38,49,50,39;,
  4;39,50,51,40;,
  4;40,51,52,41;,
  4;41,52,53,42;,
  4;42,53,54,43;,
  4;43,54,44,33;,
  4;44,55,56,45;,
  4;45,56,57,46;,
  4;46,57,58,47;,
  4;47,58,59,48;,
  4;49,60,61,50;,
  4;50,61,62,51;,
  4;51,62,63,52;,
  4;52,63,64,53;,
  4;53,64,65,54;,
  4;54,65,55,44;,
  4;55,66,67,56;,
  4;56,67,68,57;,
  4;57,68,69,58;,
  4;58,69,70,59;,
  4;60,71,72,61;,
  4;61,72,73,62;,
  4;62,73,74,63;,
  4;63,74,75,64;,
  4;64,75,76,65;,
  4;65,76,66,55;,
  4;66,77,78,67;,
  4;67,78,79,68;,
  4;68,79,80,69;,
  4;69,80,81,70;,
  4;71,82,83,72;,
  4;72,83,84,73;,
  4;73,84,85,74;,
  4;74,85,86,75;,
  4;75,86,87,76;,
  4;76,87,77,66;,
  4;77,88,89,78;,
  4;78,89,90,79;,
  4;79,90,91,80;,
  4;80,91,92,81;,
  4;82,93,94,83;,
  4;83,94,95,84;,
  4;84,95,96,85;,
  4;85,96,97,86;,
  4;86,97,98,87;,
  4;87,98,88,77;,
  3;1,99,0;,
  3;2,99,1;,
  3;3,99,2;,
  3;4,99,3;,
  3;6,99,5;,
  3;7,99,6;,
  3;8,99,7;,
  3;9,99,8;,
  3;10,99,9;,
  3;0,99,10;,
  3;88,100,89;,
  3;89,100,90;,
  3;90,100,91;,
  3;91,100,92;,
  3;93,100,94;,
  3;94,100,95;,
  3;95,100,96;,
  3;96,100,97;,
  3;97,100,98;,
  3;98,100,88;,
  4;101,101,102,102;,
  4;102,102,103,103;,
  4;103,103,104,104;,
  4;104,104,105,105;,
  4;105,105,106,106;,
  4;106,106,107,107;,
  4;107,107,108,108;,
  4;108,108,109,109;,
  4;109,109,110,110;,
  4;110,110,111,111;,
  4;111,111,112,112;,
  4;112,112,113,113;,
  4;113,113,114,114;,
  4;114,114,115,115;,
  4;115,115,116,116;,
  4;116,116,117,117;,
  4;117,117,118,118;,
  4;118,118,119,119;,
  4;119,119,120,120;,
  4;120,120,101,101;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;121,121,121;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  3;122,122,122;,
  4;123,140,143,137;,
  4;137,143,138,124;,
  4;143,139,126,138;,
  4;140,125,139,143;,
  4;125,131,144,139;,
  4;139,144,141,126;,
  4;144,142,128,141;,
  4;131,127,142,144;,
  4;127,134,145,142;,
  4;142,145,132,128;,
  4;145,133,130,132;,
  4;134,129,133,145;,
  4;129,136,146,133;,
  4;133,146,135,130;,
  4;146,137,124,135;,
  4;136,123,137,146;,
  4;124,138,147,135;,
  4;135,147,132,130;,
  4;147,141,128,132;,
  4;138,126,141,147;,
  4;129,134,148,136;,
  4;136,148,140,123;,
  4;148,131,125,140;,
  4;134,127,131,148;;
 }
 MeshTextureCoords {
  251;
  0.000000;0.100000;,
  0.000000;0.200000;,
  0.050000;0.200000;,
  0.050000;0.100000;,
  0.100000;0.200000;,
  0.100000;0.100000;,
  0.150000;0.200000;,
  0.150000;0.100000;,
  0.200000;0.200000;,
  0.200000;0.100000;,
  0.700000;0.100000;,
  0.700000;0.200000;,
  0.750000;0.200000;,
  0.750000;0.100000;,
  0.800000;0.200000;,
  0.800000;0.100000;,
  0.850000;0.200000;,
  0.850000;0.100000;,
  0.900000;0.200000;,
  0.900000;0.100000;,
  0.950000;0.200000;,
  0.950000;0.100000;,
  1.000000;0.200000;,
  1.000000;0.100000;,
  0.000000;0.300000;,
  0.050000;0.300000;,
  0.100000;0.300000;,
  0.150000;0.300000;,
  0.200000;0.300000;,
  0.700000;0.300000;,
  0.750000;0.300000;,
  0.800000;0.300000;,
  0.850000;0.300000;,
  0.900000;0.300000;,
  0.950000;0.300000;,
  1.000000;0.300000;,
  0.000000;0.400000;,
  0.050000;0.400000;,
  0.100000;0.400000;,
  0.150000;0.400000;,
  0.200000;0.400000;,
  0.700000;0.400000;,
  0.750000;0.400000;,
  0.800000;0.400000;,
  0.850000;0.400000;,
  0.900000;0.400000;,
  0.950000;0.400000;,
  1.000000;0.400000;,
  0.000000;0.500000;,
  0.050000;0.500000;,
  0.100000;0.500000;,
  0.150000;0.500000;,
  0.200000;0.500000;,
  0.700000;0.500000;,
  0.750000;0.500000;,
  0.800000;0.500000;,
  0.850000;0.500000;,
  0.900000;0.500000;,
  0.950000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.600000;,
  0.050000;0.600000;,
  0.100000;0.600000;,
  0.150000;0.600000;,
  0.200000;0.600000;,
  0.700000;0.600000;,
  0.750000;0.600000;,
  0.800000;0.600000;,
  0.850000;0.600000;,
  0.900000;0.600000;,
  0.950000;0.600000;,
  1.000000;0.600000;,
  0.000000;0.700000;,
  0.050000;0.700000;,
  0.100000;0.700000;,
  0.150000;0.700000;,
  0.200000;0.700000;,
  0.700000;0.700000;,
  0.750000;0.700000;,
  0.800000;0.700000;,
  0.850000;0.700000;,
  0.900000;0.700000;,
  0.950000;0.700000;,
  1.000000;0.700000;,
  0.000000;0.800000;,
  0.050000;0.800000;,
  0.100000;0.800000;,
  0.150000;0.800000;,
  0.200000;0.800000;,
  0.700000;0.800000;,
  0.750000;0.800000;,
  0.800000;0.800000;,
  0.850000;0.800000;,
  0.900000;0.800000;,
  0.950000;0.800000;,
  1.000000;0.800000;,
  0.000000;0.900000;,
  0.050000;0.900000;,
  0.100000;0.900000;,
  0.150000;0.900000;,
  0.200000;0.900000;,
  0.700000;0.900000;,
  0.750000;0.900000;,
  0.800000;0.900000;,
  0.850000;0.900000;,
  0.900000;0.900000;,
  0.950000;0.900000;,
  1.000000;0.900000;,
  0.025000;0.000000;,
  0.075000;0.000000;,
  0.125000;0.000000;,
  0.175000;0.000000;,
  0.725000;0.000000;,
  0.775000;0.000000;,
  0.825000;0.000000;,
  0.875000;0.000000;,
  0.925000;0.000000;,
  0.975000;0.000000;,
  0.025000;1.000000;,
  0.075000;1.000000;,
  0.125000;1.000000;,
  0.175000;1.000000;,
  0.725000;1.000000;,
  0.775000;1.000000;,
  0.825000;1.000000;,
  0.875000;1.000000;,
  0.925000;1.000000;,
  0.975000;1.000000;,
  0.375000;0.312500;,
  0.375000;0.688440;,
  0.387500;0.688440;,
  0.387500;0.312500;,
  0.400000;0.688440;,
  0.400000;0.312500;,
  0.412500;0.688440;,
  0.412500;0.312500;,
  0.425000;0.688440;,
  0.425000;0.312500;,
  0.437500;0.688440;,
  0.437500;0.312500;,
  0.450000;0.688440;,
  0.450000;0.312500;,
  0.462500;0.688440;,
  0.462500;0.312500;,
  0.475000;0.688440;,
  0.475000;0.312500;,
  0.487500;0.688440;,
  0.487500;0.312500;,
  0.500000;0.688440;,
  0.500000;0.312500;,
  0.512500;0.688440;,
  0.512500;0.312500;,
  0.525000;0.688440;,
  0.525000;0.312500;,
  0.537500;0.688440;,
  0.537500;0.312500;,
  0.550000;0.688440;,
  0.550000;0.312500;,
  0.562500;0.688440;,
  0.562500;0.312500;,
  0.575000;0.688440;,
  0.575000;0.312500;,
  0.587500;0.688440;,
  0.587500;0.312500;,
  0.600000;0.688440;,
  0.600000;0.312500;,
  0.612500;0.688440;,
  0.612500;0.312500;,
  0.625000;0.688440;,
  0.625000;0.312500;,
  0.626410;0.064410;,
  0.500000;0.150000;,
  0.648600;0.107970;,
  0.591840;0.029840;,
  0.548280;0.007650;,
  0.500000;-0.000000;,
  0.451720;0.007650;,
  0.408160;0.029840;,
  0.373590;0.064410;,
  0.351400;0.107970;,
  0.343750;0.156250;,
  0.351400;0.204530;,
  0.373590;0.248090;,
  0.408160;0.282660;,
  0.451720;0.304850;,
  0.500000;0.312500;,
  0.548280;0.304850;,
  0.591840;0.282660;,
  0.626410;0.248090;,
  0.648600;0.204530;,
  0.656250;0.156250;,
  0.648600;0.892030;,
  0.500000;0.837500;,
  0.626410;0.935590;,
  0.591840;0.970160;,
  0.548280;0.992350;,
  0.500000;1.000000;,
  0.451720;0.992350;,
  0.408160;0.970160;,
  0.373590;0.935590;,
  0.351400;0.892030;,
  0.343750;0.843750;,
  0.351400;0.795470;,
  0.373590;0.751910;,
  0.408160;0.717340;,
  0.451720;0.695150;,
  0.500000;0.687500;,
  0.548280;0.695150;,
  0.591840;0.717340;,
  0.626410;0.751910;,
  0.648600;0.795470;,
  0.656250;0.843750;,
  0.375000;0.000000;,
  0.375000;0.125000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.125000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.125000;0.250000;;
 }
}
