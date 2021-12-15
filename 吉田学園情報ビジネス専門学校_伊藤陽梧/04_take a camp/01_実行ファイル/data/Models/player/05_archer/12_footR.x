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
 39;
 -0.20326;-0.53493;-0.83775;,
 -0.26136;-0.24263;-0.72265;,
 0.00114;-0.24263;-0.88515;,
 0.00114;-0.52603;-0.96415;,
 0.26354;-0.24263;-0.72265;,
 0.20554;-0.53493;-0.83775;,
 0.00114;-0.05753;-0.52925;,
 0.20554;-0.11673;-0.52215;,
 -0.20326;-0.11673;-0.52215;,
 -0.26976;-0.02793;-0.23525;,
 0.00114;0.00697;-0.23525;,
 0.27194;-0.02793;-0.23525;,
 0.00114;-0.00653;0.25215;,
 0.21104;-0.03263;0.12575;,
 -0.20886;-0.03263;0.12575;,
 -0.28236;-0.24263;0.14475;,
 0.00114;-0.24263;0.29135;,
 0.28454;-0.24263;0.14475;,
 0.00114;-0.52603;0.25215;,
 0.21104;-0.53493;0.12575;,
 -0.20886;-0.53493;0.12575;,
 -0.26136;-0.52603;-0.23525;,
 0.00114;-0.53783;-0.23525;,
 0.26354;-0.52603;-0.23525;,
 0.00114;-0.52603;-0.96415;,
 0.20554;-0.53493;-0.83775;,
 -0.20326;-0.53493;-0.83775;,
 0.33814;-0.24263;-0.23525;,
 0.26354;-0.52603;-0.23525;,
 0.28454;-0.24263;0.14475;,
 0.21104;-0.53493;0.12575;,
 0.27194;-0.02793;-0.23525;,
 0.21104;-0.03263;0.12575;,
 -0.20886;-0.53493;0.12575;,
 -0.28236;-0.24263;0.14475;,
 -0.33596;-0.24263;-0.23525;,
 -0.26136;-0.52603;-0.23525;,
 -0.26976;-0.02793;-0.23525;,
 -0.20886;-0.03263;0.12575;;
 
 24;
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
 4;34,38,37,35;;
 
 MeshMaterialList {
  8;
  24;
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
  42;
  -0.843831;0.012030;-0.536474;,
  0.843880;0.012134;-0.536395;,
  -0.487496;0.806225;-0.335183;,
  0.487607;0.806170;-0.335155;,
  -0.133615;0.990551;0.030933;,
  0.133670;0.990543;0.030936;,
  -0.801379;-0.220165;0.556164;,
  0.801429;-0.220160;0.556094;,
  -0.622686;0.777616;-0.087034;,
  0.819474;0.030447;0.572308;,
  0.000087;-0.164769;0.986332;,
  -0.819422;0.030448;0.572381;,
  0.007138;-0.999975;0.000089;,
  -0.007133;-0.999975;0.000087;,
  -0.516038;0.226916;-0.825962;,
  0.616875;0.560814;-0.552226;,
  0.000024;0.929582;-0.368615;,
  -0.616763;0.560885;-0.552279;,
  0.448848;0.878074;-0.165893;,
  0.000028;0.999513;0.031214;,
  -0.426586;0.584383;-0.690305;,
  0.000020;0.992839;-0.119460;,
  0.000088;0.024956;0.999689;,
  0.000003;-1.000000;0.000088;,
  0.996893;0.077515;-0.014015;,
  -0.996889;0.077545;-0.014072;,
  0.516102;0.226970;-0.825908;,
  0.426647;0.584377;-0.690272;,
  -0.786015;0.277092;0.552630;,
  0.000087;0.214370;0.976753;,
  0.786067;0.277087;0.552559;,
  -0.008563;-0.999959;0.003052;,
  0.000001;-0.999995;0.003053;,
  0.008565;-0.999959;0.003053;,
  0.000004;-0.999996;-0.002877;,
  0.005712;-0.999980;-0.002876;,
  -0.005704;-0.999980;-0.002878;,
  0.971312;-0.205582;-0.119536;,
  0.973108;-0.230230;0.007412;,
  0.937768;0.314519;0.147207;,
  -0.973093;-0.230296;0.007374;,
  -0.971275;-0.205712;-0.119612;;
  24;
  4;0,17,20,14;,
  4;26,27,15,1;,
  4;27,16,3,15;,
  4;17,2,16,20;,
  4;2,8,21,16;,
  4;16,21,18,3;,
  4;21,19,5,18;,
  4;8,4,19,21;,
  4;28,11,22,29;,
  4;29,22,9,30;,
  4;22,10,7,9;,
  4;11,6,10,22;,
  4;31,13,23,32;,
  4;32,23,12,33;,
  4;23,34,35,12;,
  4;13,36,34,23;,
  4;1,37,24,38;,
  4;38,24,9,7;,
  4;24,39,30,9;,
  4;15,3,18,24;,
  4;6,11,25,40;,
  4;40,25,41,0;,
  4;25,8,2,17;,
  4;11,28,8,25;;
 }
 MeshTextureCoords {
  39;
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
