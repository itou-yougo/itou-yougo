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
 78;
 -0.05339;0.13062;-0.09509;,
 0.00431;0.00042;-0.12869;,
 -0.21829;0.00042;-0.17179;,
 -0.21829;0.17622;-0.12869;,
 -0.44089;0.00042;-0.12869;,
 -0.38319;0.13062;-0.09509;,
 -0.21829;-0.17528;-0.12869;,
 -0.38319;-0.12978;-0.09509;,
 -0.05339;-0.12978;-0.09509;,
 0.00431;-0.17528;0.00071;,
 -0.21829;-0.23388;0.00071;,
 -0.44089;-0.17528;0.00071;,
 -0.21829;-0.17528;0.13011;,
 -0.38319;-0.12978;0.09651;,
 -0.05339;-0.12978;0.09651;,
 0.00431;0.00042;0.13011;,
 -0.21829;0.00042;0.17321;,
 -0.44089;0.00042;0.13011;,
 -0.21829;0.17622;0.13011;,
 -0.38319;0.13062;0.09651;,
 -0.05339;0.13062;0.09651;,
 0.00431;0.17622;0.00071;,
 -0.21829;0.23482;0.00071;,
 -0.44089;0.17622;0.00071;,
 -0.21829;0.17622;-0.12869;,
 -0.38319;0.13062;-0.09509;,
 -0.05339;0.13062;-0.09509;,
 -0.51499;0.00042;0.00071;,
 -0.44089;0.17622;0.00071;,
 -0.44089;0.00042;0.13011;,
 -0.38319;0.13062;0.09651;,
 -0.44089;-0.17528;0.00071;,
 -0.38319;-0.12978;0.09651;,
 -0.05339;0.13062;0.09651;,
 0.00431;0.00042;0.13011;,
 0.07841;0.00042;0.00071;,
 0.00431;0.17622;0.00071;,
 0.00431;-0.17528;0.00071;,
 -0.05339;-0.12978;0.09651;,
 0.05041;0.10242;-0.09509;,
 0.06801;0.00042;-0.12869;,
 0.00021;0.00042;-0.17179;,
 0.00021;0.13812;-0.12869;,
 -0.06749;0.00042;-0.12869;,
 -0.04989;0.10242;-0.09509;,
 0.00021;-0.13718;-0.12869;,
 -0.04989;-0.10148;-0.09509;,
 0.05041;-0.10148;-0.09509;,
 0.06801;-0.13718;0.00071;,
 0.00021;-0.18308;0.00071;,
 -0.06749;-0.13718;0.00071;,
 0.00021;-0.13718;0.13011;,
 -0.04989;-0.10148;0.09651;,
 0.05041;-0.10148;0.09651;,
 0.06801;0.00042;0.13011;,
 0.00021;0.00042;0.17321;,
 -0.06749;0.00042;0.13011;,
 0.00021;0.13812;0.13011;,
 -0.04989;0.10242;0.09651;,
 0.05041;0.10242;0.09651;,
 0.06801;0.13812;0.00071;,
 0.00021;0.18392;0.00071;,
 -0.06749;0.13812;0.00071;,
 0.00021;0.13812;-0.12869;,
 -0.04989;0.10242;-0.09509;,
 0.05041;0.10242;-0.09509;,
 -0.09009;0.00042;0.00071;,
 -0.06749;0.13812;0.00071;,
 -0.06749;0.00042;0.13011;,
 -0.04989;0.10242;0.09651;,
 -0.06749;-0.13718;0.00071;,
 -0.04989;-0.10148;0.09651;,
 0.05041;0.10242;0.09651;,
 0.06801;0.00042;0.13011;,
 0.09061;0.00042;0.00071;,
 0.06801;0.13812;0.00071;,
 0.06801;-0.13718;0.00071;,
 0.05041;-0.10148;0.09651;;
 
 48;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;2,6,7,4;,
 4;1,8,6,2;,
 4;8,9,10,6;,
 4;6,10,11,7;,
 4;10,12,13,11;,
 4;9,14,12,10;,
 4;14,15,16,12;,
 4;12,16,17,13;,
 4;16,18,19,17;,
 4;15,20,18,16;,
 4;20,21,22,18;,
 4;18,22,23,19;,
 4;22,24,25,23;,
 4;21,26,24,22;,
 4;5,4,27,28;,
 4;28,27,29,30;,
 4;27,31,32,29;,
 4;4,7,31,27;,
 4;33,34,35,36;,
 4;36,35,1,0;,
 4;35,37,8,1;,
 4;34,38,37,35;,
 4;39,40,41,42;,
 4;42,41,43,44;,
 4;41,45,46,43;,
 4;40,47,45,41;,
 4;47,48,49,45;,
 4;45,49,50,46;,
 4;49,51,52,50;,
 4;48,53,51,49;,
 4;53,54,55,51;,
 4;51,55,56,52;,
 4;55,57,58,56;,
 4;54,59,57,55;,
 4;59,60,61,57;,
 4;57,61,62,58;,
 4;61,63,64,62;,
 4;60,65,63,61;,
 4;44,43,66,67;,
 4;67,66,68,69;,
 4;66,70,71,68;,
 4;43,46,70,66;,
 4;72,73,74,75;,
 4;75,74,40,39;,
 4;74,76,47,40;,
 4;73,77,76,74;;
 
 MeshMaterialList {
  8;
  48;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
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
   TextureFilename {
    "data/TEXTURE/head.png";
   }
  }
  Material {
   0.081600;0.016000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.760000;0.448000;0.224000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.241600;0.106400;0.000000;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.568000;0.336000;0.168000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  62;
  0.455321;0.550789;-0.699510;,
  -0.455321;0.550789;-0.699510;,
  0.455267;-0.550964;-0.699407;,
  -0.455267;-0.550964;-0.699407;,
  0.455267;-0.550964;0.699407;,
  -0.455267;-0.550964;0.699407;,
  0.455322;0.550789;0.699510;,
  -0.455321;0.550789;0.699510;,
  0.640615;-0.767862;-0.000000;,
  -0.557431;-0.000046;0.830223;,
  -0.000000;0.626915;0.779088;,
  0.557431;-0.000046;0.830223;,
  -0.640777;0.767727;-0.000000;,
  0.640777;0.767727;-0.000000;,
  -0.000000;0.626914;-0.779088;,
  -0.557431;-0.000046;-0.830224;,
  -0.000000;-0.627094;-0.778944;,
  0.557431;-0.000046;-0.830223;,
  -0.640615;-0.767863;-0.000000;,
  -0.000000;-0.627094;0.778943;,
  -0.000000;-0.000034;-1.000000;,
  -0.000000;-1.000000;-0.000000;,
  -0.000000;-0.000034;1.000000;,
  -0.000000;1.000000;-0.000000;,
  -0.824881;-0.000053;-0.565307;,
  0.824882;-0.000053;0.565305;,
  0.770377;0.439173;-0.462219;,
  -0.770712;0.438890;-0.461929;,
  0.770424;-0.439103;-0.462207;,
  -0.770759;-0.438820;-0.461917;,
  0.770424;-0.439104;0.462207;,
  -0.770759;-0.438820;0.461917;,
  0.770377;0.439173;0.462219;,
  -0.770712;0.438890;0.461929;,
  0.858998;-0.511979;-0.000000;,
  -0.847673;-0.000105;0.530519;,
  -0.619397;0.541330;0.568603;,
  0.847458;-0.000105;0.530862;,
  -0.859085;0.511833;-0.000000;,
  0.858876;0.512183;-0.000000;,
  0.618764;0.541680;-0.568959;,
  -0.847673;-0.000105;-0.530519;,
  -0.619551;-0.541162;-0.568596;,
  0.847458;-0.000105;-0.530862;,
  -0.859206;-0.511629;-0.000000;,
  -0.619551;-0.541162;0.568595;,
  0.604269;-0.000116;-0.796780;,
  0.627988;-0.778223;-0.000000;,
  0.604270;-0.000116;0.796780;,
  0.627496;0.778620;-0.000000;,
  -1.000000;-0.000083;-0.000000;,
  1.000000;-0.000083;-0.000000;,
  -0.824881;-0.000053;0.565306;,
  0.824882;-0.000053;-0.565306;,
  -0.619397;0.541330;-0.568603;,
  -0.604934;-0.000116;-0.796275;,
  0.618917;-0.541512;-0.568952;,
  -0.628647;-0.777691;-0.000000;,
  0.618918;-0.541512;0.568951;,
  -0.604935;-0.000116;0.796275;,
  0.618764;0.541680;0.568959;,
  -0.628155;0.778088;-0.000000;;
  48;
  4;0,17,20,14;,
  4;14,20,15,1;,
  4;20,16,3,15;,
  4;17,2,16,20;,
  4;2,8,21,16;,
  4;16,21,18,3;,
  4;21,19,5,18;,
  4;8,4,19,21;,
  4;4,11,22,19;,
  4;19,22,9,5;,
  4;22,10,7,9;,
  4;11,6,10,22;,
  4;6,13,23,10;,
  4;10,23,12,7;,
  4;23,14,1,12;,
  4;13,0,14,23;,
  4;1,15,24,12;,
  4;12,52,9,7;,
  4;52,18,5,9;,
  4;15,3,18,24;,
  4;6,11,25,13;,
  4;13,53,17,0;,
  4;53,8,2,17;,
  4;11,4,8,25;,
  4;26,43,46,40;,
  4;54,55,41,27;,
  4;55,42,29,41;,
  4;43,28,56,46;,
  4;28,34,47,56;,
  4;42,57,44,29;,
  4;57,45,31,44;,
  4;34,30,58,47;,
  4;30,37,48,58;,
  4;45,59,35,31;,
  4;59,36,33,35;,
  4;37,32,60,48;,
  4;32,39,49,60;,
  4;36,61,38,33;,
  4;61,54,27,38;,
  4;39,26,40,49;,
  4;27,41,50,38;,
  4;38,50,35,33;,
  4;50,44,31,35;,
  4;41,29,44,50;,
  4;32,37,51,39;,
  4;39,51,43,26;,
  4;51,34,28,43;,
  4;37,30,34,51;;
 }
 MeshTextureCoords {
  78;
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
  0.125000;0.250000;,
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
