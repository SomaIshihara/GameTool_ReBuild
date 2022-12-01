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
 117;
 0.00000;6.05559;0.00000;,
 0.98326;5.77900;-0.98326;,
 0.00000;5.77900;-1.39053;,
 0.00000;6.05559;0.00000;,
 1.39053;5.77900;0.00000;,
 0.00000;6.05559;0.00000;,
 0.98326;5.77900;0.98326;,
 0.00000;6.05559;0.00000;,
 -0.00000;5.77900;1.39053;,
 0.00000;6.05559;0.00000;,
 -0.98326;5.77900;0.98326;,
 0.00000;6.05559;0.00000;,
 -1.39053;5.77900;-0.00000;,
 0.00000;6.05559;0.00000;,
 -0.98326;5.77900;-0.98326;,
 0.00000;6.05559;0.00000;,
 0.00000;5.77900;-1.39053;,
 1.81682;4.99133;-1.81682;,
 0.00000;4.99133;-2.56937;,
 2.56937;4.99133;0.00000;,
 1.81682;4.99133;1.81682;,
 -0.00000;4.99133;2.56937;,
 -1.81682;4.99133;1.81682;,
 -2.56937;4.99133;-0.00000;,
 -1.81682;4.99133;-1.81682;,
 0.00000;4.99133;-2.56937;,
 2.37379;3.81249;-2.37379;,
 0.00000;3.81249;-3.35704;,
 3.35704;3.81249;0.00000;,
 2.37379;3.81249;2.37379;,
 -0.00000;3.81249;3.35704;,
 -2.37379;3.81249;2.37379;,
 -3.35704;3.81249;-0.00000;,
 -2.37379;3.81249;-2.37379;,
 0.00000;3.81249;-3.35704;,
 0.00000;5.93806;0.00000;,
 0.09899;5.93806;-0.09899;,
 0.00000;5.93806;-0.14000;,
 0.14000;5.93806;0.00000;,
 0.09899;5.93806;0.09899;,
 -0.00000;5.93806;0.14000;,
 -0.09899;5.93806;0.09899;,
 -0.14000;5.93806;-0.00000;,
 -0.09899;5.93806;-0.09899;,
 0.36959;5.86194;-0.36959;,
 0.00000;5.86194;-0.52268;,
 0.52268;5.86194;0.00000;,
 0.36959;5.86194;0.36959;,
 -0.00000;5.86194;0.52268;,
 -0.36959;5.86194;0.36959;,
 -0.52268;5.86194;-0.00000;,
 -0.36959;5.86194;-0.36959;,
 0.59899;5.64516;-0.59899;,
 0.00000;5.64516;-0.84711;,
 0.84711;5.64516;0.00000;,
 0.59899;5.64516;0.59899;,
 -0.00000;5.64516;0.84711;,
 -0.59900;5.64516;0.59899;,
 -0.84711;5.64516;-0.00000;,
 -0.59900;5.64516;-0.59899;,
 0.75228;5.32074;-0.75228;,
 0.00000;5.32074;-1.06388;,
 1.06388;5.32074;0.00000;,
 0.75228;5.32074;0.75228;,
 -0.00000;5.32074;1.06388;,
 -0.75228;5.32074;0.75228;,
 -1.06388;5.32074;-0.00000;,
 -0.75228;5.32074;-0.75228;,
 0.80610;4.93806;-0.80610;,
 0.00000;4.93806;-1.14000;,
 1.14000;4.93806;0.00000;,
 0.80610;4.93806;0.80610;,
 -0.00000;4.93806;1.14000;,
 -0.80610;4.93806;0.80610;,
 -1.14000;4.93806;-0.00000;,
 -0.80610;4.93806;-0.80610;,
 0.80610;-1.23194;-0.80610;,
 0.00000;-1.23194;-1.14000;,
 1.14000;-1.23194;0.00000;,
 0.80610;-1.23194;0.80610;,
 -0.00000;-1.23194;1.14000;,
 -0.80610;-1.23194;0.80610;,
 -1.14000;-1.23194;-0.00000;,
 -0.80610;-1.23194;-0.80610;,
 0.75228;-1.61463;-0.75228;,
 0.00000;-1.61463;-1.06388;,
 1.06388;-1.61463;0.00000;,
 0.75228;-1.61463;0.75228;,
 -0.00000;-1.61463;1.06388;,
 -0.75228;-1.61463;0.75228;,
 -1.06388;-1.61463;-0.00000;,
 -0.75228;-1.61463;-0.75228;,
 0.59899;-1.93905;-0.59899;,
 0.00000;-1.93905;-0.84711;,
 0.84711;-1.93905;0.00000;,
 0.59899;-1.93905;0.59899;,
 -0.00000;-1.93905;0.84711;,
 -0.59900;-1.93905;0.59899;,
 -0.84711;-1.93905;-0.00000;,
 -0.59900;-1.93905;-0.59899;,
 0.36959;-2.15582;-0.36959;,
 0.00000;-2.15582;-0.52268;,
 0.52268;-2.15582;0.00000;,
 0.36959;-2.15582;0.36959;,
 -0.00000;-2.15582;0.52268;,
 -0.36959;-2.15582;0.36959;,
 -0.52268;-2.15582;-0.00000;,
 -0.36959;-2.15582;-0.36959;,
 0.09899;-2.23194;-0.09899;,
 0.00000;-2.23194;-0.14000;,
 0.14000;-2.23194;0.00000;,
 0.09899;-2.23194;0.09899;,
 -0.00000;-2.23194;0.14000;,
 -0.09899;-2.23194;0.09899;,
 -0.14000;-2.23194;-0.00000;,
 -0.09899;-2.23194;-0.09899;,
 0.00000;-2.23194;-0.00000;;
 
 112;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 3;35,36,37;,
 3;35,38,36;,
 3;35,39,38;,
 3;35,40,39;,
 3;35,41,40;,
 3;35,42,41;,
 3;35,43,42;,
 3;35,37,43;,
 4;37,36,44,45;,
 4;36,38,46,44;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,41,49,48;,
 4;41,42,50,49;,
 4;42,43,51,50;,
 4;43,37,45,51;,
 4;45,44,52,53;,
 4;44,46,54,52;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,49,57,56;,
 4;49,50,58,57;,
 4;50,51,59,58;,
 4;51,45,53,59;,
 4;53,52,60,61;,
 4;52,54,62,60;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,57,65,64;,
 4;57,58,66,65;,
 4;58,59,67,66;,
 4;59,53,61,67;,
 4;61,60,68,69;,
 4;60,62,70,68;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,65,73,72;,
 4;65,66,74,73;,
 4;66,67,75,74;,
 4;67,61,69,75;,
 4;69,68,76,77;,
 4;68,70,78,76;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,73,81,80;,
 4;73,74,82,81;,
 4;74,75,83,82;,
 4;75,69,77,83;,
 4;77,76,84,85;,
 4;76,78,86,84;,
 4;78,79,87,86;,
 4;79,80,88,87;,
 4;80,81,89,88;,
 4;81,82,90,89;,
 4;82,83,91,90;,
 4;83,77,85,91;,
 4;85,84,92,93;,
 4;84,86,94,92;,
 4;86,87,95,94;,
 4;87,88,96,95;,
 4;88,89,97,96;,
 4;89,90,98,97;,
 4;90,91,99,98;,
 4;91,85,93,99;,
 4;93,92,100,101;,
 4;92,94,102,100;,
 4;94,95,103,102;,
 4;95,96,104,103;,
 4;96,97,105,104;,
 4;97,98,106,105;,
 4;98,99,107,106;,
 4;99,93,101,107;,
 4;101,100,108,109;,
 4;100,102,110,108;,
 4;102,103,111,110;,
 4;103,104,112,111;,
 4;104,105,113,112;,
 4;105,106,114,113;,
 4;106,107,115,114;,
 4;107,101,109,115;,
 3;109,108,116;,
 3;108,110,116;,
 3;110,111,116;,
 3;111,112,116;,
 3;112,113,116;,
 3;113,114,116;,
 3;114,115,116;,
 3;115,109,116;;
 
 MeshMaterialList {
  3;
  112;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.517647;0.109804;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.743529;0.611765;1.000000;;
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
  107;
  -0.000000;1.000000;0.000000;,
  0.000000;0.924735;-0.380611;,
  0.269133;0.924735;-0.269133;,
  0.380611;0.924735;0.000000;,
  0.269133;0.924735;0.269133;,
  -0.000000;0.924735;0.380611;,
  -0.269133;0.924735;0.269133;,
  -0.380611;0.924735;0.000000;,
  -0.269133;0.924735;-0.269133;,
  -0.000000;0.709230;-0.704977;,
  0.498494;0.709230;-0.498494;,
  0.704977;0.709230;0.000000;,
  0.498494;0.709230;0.498494;,
  -0.000000;0.709230;0.704977;,
  -0.498494;0.709230;0.498494;,
  -0.704977;0.709230;0.000000;,
  -0.498494;0.709230;-0.498494;,
  -0.000000;0.555571;-0.831469;,
  0.587938;0.555571;-0.587938;,
  0.831469;0.555571;0.000000;,
  0.587938;0.555570;0.587938;,
  -0.000000;0.555571;0.831469;,
  -0.587938;0.555570;0.587938;,
  -0.831469;0.555571;0.000000;,
  -0.587938;0.555570;-0.587938;,
  0.000000;1.000000;0.000000;,
  0.000000;0.995200;-0.097858;,
  0.069196;0.995200;-0.069196;,
  0.097858;0.995200;0.000000;,
  0.069196;0.995200;0.069196;,
  -0.000000;0.995200;0.097858;,
  -0.069196;0.995200;0.069196;,
  -0.097858;0.995200;-0.000000;,
  -0.069196;0.995200;-0.069196;,
  -0.000000;0.924735;-0.380611;,
  0.269132;0.924735;-0.269132;,
  0.380611;0.924735;0.000000;,
  0.269132;0.924735;0.269132;,
  -0.000000;0.924735;0.380611;,
  -0.269132;0.924735;0.269132;,
  -0.380611;0.924735;-0.000000;,
  -0.269132;0.924735;-0.269132;,
  -0.000000;0.709230;-0.704977;,
  0.498494;0.709230;-0.498494;,
  0.704977;0.709230;0.000000;,
  0.498494;0.709230;0.498494;,
  -0.000000;0.709230;0.704977;,
  -0.498494;0.709230;0.498494;,
  -0.704977;0.709230;-0.000000;,
  -0.498494;0.709230;-0.498494;,
  -0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  -0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;-0.000000;,
  -0.652733;0.384551;-0.652733;,
  -0.000000;0.098154;-0.995171;,
  0.703692;0.098154;-0.703692;,
  0.995171;0.098154;0.000000;,
  0.703692;0.098154;0.703692;,
  -0.000000;0.098154;0.995171;,
  -0.703692;0.098154;0.703692;,
  -0.995171;0.098154;-0.000000;,
  -0.703692;0.098154;-0.703692;,
  -0.000000;-0.098154;-0.995171;,
  0.703692;-0.098154;-0.703692;,
  0.995171;-0.098154;0.000000;,
  0.703692;-0.098154;0.703692;,
  -0.000000;-0.098154;0.995171;,
  -0.703692;-0.098154;0.703692;,
  -0.995171;-0.098154;-0.000000;,
  -0.703692;-0.098154;-0.703692;,
  -0.000000;-0.384551;-0.923104;,
  0.652733;-0.384551;-0.652733;,
  0.923104;-0.384551;0.000000;,
  0.652733;-0.384551;0.652733;,
  -0.000000;-0.384551;0.923104;,
  -0.652733;-0.384551;0.652733;,
  -0.923104;-0.384551;-0.000000;,
  -0.652733;-0.384551;-0.652733;,
  -0.000000;-0.709230;-0.704977;,
  0.498494;-0.709230;-0.498494;,
  0.704977;-0.709230;0.000000;,
  0.498494;-0.709230;0.498494;,
  -0.000000;-0.709230;0.704977;,
  -0.498494;-0.709230;0.498494;,
  -0.704977;-0.709230;-0.000000;,
  -0.498494;-0.709230;-0.498494;,
  -0.000000;-0.924735;-0.380611;,
  0.269132;-0.924735;-0.269132;,
  0.380611;-0.924735;0.000000;,
  0.269132;-0.924735;0.269132;,
  -0.000000;-0.924735;0.380611;,
  -0.269132;-0.924735;0.269132;,
  -0.380611;-0.924735;-0.000000;,
  -0.269132;-0.924735;-0.269132;,
  0.000000;-0.995200;-0.097858;,
  0.069196;-0.995200;-0.069196;,
  0.097858;-0.995200;0.000000;,
  0.069196;-0.995200;0.069196;,
  -0.000000;-0.995200;0.097858;,
  -0.069196;-0.995200;0.069196;,
  -0.097858;-0.995200;-0.000000;,
  -0.069196;-0.995200;-0.069196;,
  0.000000;-1.000000;-0.000000;;
  112;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  3;25,27,26;,
  3;25,28,27;,
  3;25,29,28;,
  3;25,30,29;,
  3;25,31,30;,
  3;25,32,31;,
  3;25,33,32;,
  3;25,26,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,33,41,40;,
  4;33,26,34,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,41,49,48;,
  4;41,34,42,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,49,57,56;,
  4;49,42,50,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,57,65,64;,
  4;57,50,58,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,65,73,72;,
  4;65,58,66,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,73,81,80;,
  4;73,66,74,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,81,89,88;,
  4;81,74,82,89;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,89,97,96;,
  4;89,82,90,97;,
  4;90,91,99,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,90,98,105;,
  3;98,99,106;,
  3;99,100,106;,
  3;100,101,106;,
  3;101,102,106;,
  3;102,103,106;,
  3;103,104,106;,
  3;104,105,106;,
  3;105,98,106;;
 }
 MeshTextureCoords {
  117;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
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