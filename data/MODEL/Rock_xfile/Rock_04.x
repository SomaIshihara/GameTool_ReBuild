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
 277;
 5.17819;1.20865;1.78670;,
 6.44317;0.81267;-1.92687;,
 5.78372;5.74780;-1.16874;,
 5.04053;5.69829;1.96566;,
 5.04053;5.69829;1.96566;,
 3.98197;5.90211;3.58259;,
 5.17819;1.20865;1.78670;,
 2.05442;0.61190;5.10144;,
 3.07200;4.53346;5.31793;,
 3.04356;3.28797;5.59482;,
 2.45021;2.60335;5.86024;,
 2.45021;2.60335;5.86024;,
 1.77807;4.44380;6.12191;,
 2.05442;0.61190;5.10144;,
 -1.48939;0.88373;6.47961;,
 -0.09933;5.99930;6.18194;,
 -1.75735;5.70173;6.54648;,
 -1.48939;0.88373;6.47961;,
 -1.75735;5.70173;6.54648;,
 -5.07981;0.26353;5.61740;,
 -3.19754;6.36888;6.10836;,
 -4.77604;4.62089;6.09742;,
 -5.04898;3.22744;6.45398;,
 -5.62245;1.97395;6.17570;,
 -5.07981;0.26353;5.61740;,
 -5.62245;1.97395;6.17570;,
 -6.57239;0.13557;2.93713;,
 -6.15572;2.82728;5.25816;,
 -7.26491;1.85309;3.48609;,
 -7.26491;1.85309;3.48609;,
 -6.72049;3.92435;2.02090;,
 -6.57239;0.13557;2.93713;,
 -5.38247;0.28103;-0.97296;,
 -6.00679;4.01072;-0.15235;,
 -5.47141;2.72039;-1.65426;,
 -5.38247;0.28103;-0.97296;,
 -5.47141;2.72039;-1.65426;,
 -1.79162;-0.02909;-4.83100;,
 -3.12573;3.25334;-4.06145;,
 -1.41712;1.18821;-5.67215;,
 1.79446;0.14353;-5.96415;,
 -1.79162;-0.02909;-4.83100;,
 -1.41712;1.18821;-5.67215;,
 1.76084;2.16855;-6.25613;,
 1.79446;0.14353;-5.96415;,
 1.76084;2.16855;-6.25613;,
 5.37570;0.34187;-4.93609;,
 3.42400;5.88587;-4.80980;,
 5.33967;4.42895;-4.91126;,
 3.92678;6.55584;-4.33637;,
 4.63585;5.85336;-4.72122;,
 4.44499;6.30498;-4.39619;,
 5.37570;0.34187;-4.93609;,
 5.33967;4.42895;-4.91126;,
 6.44317;0.81267;-1.92687;,
 5.11532;5.97339;-3.95484;,
 5.23488;6.42516;-2.63410;,
 5.78372;5.74780;-1.16874;,
 5.78372;5.74780;-1.16874;,
 5.08337;7.21402;-0.95658;,
 5.04053;5.69829;1.96566;,
 4.59119;8.38904;0.62487;,
 4.22407;7.61577;2.22409;,
 -1.75735;5.70173;6.54648;,
 -0.09933;5.99930;6.18194;,
 -0.30698;7.07795;5.74216;,
 -1.43156;7.08842;6.09436;,
 5.78372;5.74780;-1.16874;,
 5.23488;6.42516;-2.63410;,
 4.71040;7.24791;-1.90719;,
 5.08337;7.21402;-0.95658;,
 4.59119;8.38904;0.62487;,
 4.11067;10.27784;1.39915;,
 4.22407;7.61577;2.22409;,
 3.89158;10.52331;2.20452;,
 3.80032;9.19473;2.60354;,
 4.71040;7.24791;-1.90719;,
 3.94271;8.48057;-1.86100;,
 5.08337;7.21402;-0.95658;,
 4.59119;8.38904;0.62487;,
 3.64823;9.29115;-1.14609;,
 3.42224;10.53491;0.32003;,
 4.11067;10.27784;1.39915;,
 3.67123;11.06096;1.15596;,
 3.51930;7.08854;3.24664;,
 3.98197;5.90211;3.58259;,
 5.04053;5.69829;1.96566;,
 4.22407;7.61577;2.22409;,
 3.98197;5.90211;3.58259;,
 3.51930;7.08854;3.24664;,
 3.07200;4.53346;5.31793;,
 3.08578;8.09108;3.43752;,
 2.38189;8.31146;3.88301;,
 1.77807;4.44380;6.12191;,
 0.59884;7.76830;5.11799;,
 -0.09933;5.99930;6.18194;,
 -0.30698;7.07795;5.74216;,
 3.26152;10.35277;2.77515;,
 3.08125;11.56448;2.44045;,
 2.38189;8.31146;3.88301;,
 2.10656;12.62559;2.43050;,
 0.59884;7.76830;5.11799;,
 1.48023;12.40217;2.70786;,
 0.09908;10.43412;3.45576;,
 -0.27061;8.30095;5.29333;,
 -0.28776;9.18190;4.64028;,
 3.80032;9.19473;2.60354;,
 3.08578;8.09108;3.43752;,
 3.51930;7.08854;3.24664;,
 4.22407;7.61577;2.22409;,
 4.11067;10.27784;1.39915;,
 3.67123;11.06096;1.15596;,
 3.89158;10.52331;2.20452;,
 3.15639;12.20576;1.80796;,
 3.60396;10.98781;2.39948;,
 3.38828;11.59316;2.25635;,
 3.89158;10.52331;2.20452;,
 3.60396;10.98781;2.39948;,
 3.80032;9.19473;2.60354;,
 3.08578;8.09108;3.43752;,
 3.26152;10.35277;2.77515;,
 2.38189;8.31146;3.88301;,
 0.59884;7.76830;5.11799;,
 -0.27061;8.30095;5.29333;,
 -0.30698;7.07795;5.74216;,
 -1.16894;8.39413;5.63295;,
 -1.43156;7.08842;6.09436;,
 -1.84891;7.96423;5.94025;,
 -0.27061;8.30095;5.29333;,
 -0.28776;9.18190;4.64028;,
 -1.24196;8.78404;5.15739;,
 -1.16894;8.39413;5.63295;,
 2.43075;6.47331;-3.98322;,
 3.42400;5.88587;-4.80980;,
 -1.50637;5.32620;-3.64748;,
 1.76084;2.16855;-6.25613;,
 -3.12573;3.25334;-4.06145;,
 -1.41712;1.18821;-5.67215;,
 -2.83782;6.46317;-1.13621;,
 -1.50637;5.32620;-3.64748;,
 -4.11159;5.80577;-0.50493;,
 -4.72387;5.45521;-0.34819;,
 -6.00679;4.01072;-0.15235;,
 -5.47141;2.72039;-1.65426;,
 -3.12573;3.25334;-4.06145;,
 3.38828;11.59316;2.25635;,
 3.08125;11.56448;2.44045;,
 3.26152;10.35277;2.77515;,
 3.60396;10.98781;2.39948;,
 2.13864;13.04426;2.06762;,
 1.14076;12.07050;2.17706;,
 1.48023;12.40217;2.70786;,
 2.10656;12.62559;2.43050;,
 -4.40029;5.87468;-0.03055;,
 -4.11159;5.80577;-0.50493;,
 -4.72387;5.45521;-0.34819;,
 -2.65071;8.50471;1.16324;,
 -2.83782;6.46317;-1.13621;,
 -3.40298;8.11075;1.72140;,
 -4.17389;6.71179;1.10992;,
 -4.40029;5.87468;-0.03055;,
 -4.11159;5.80577;-0.50493;,
 -2.83872;7.69985;5.55509;,
 -2.91730;8.38044;4.73152;,
 -3.19754;6.36888;6.10836;,
 -4.77604;4.62089;6.09742;,
 -3.10215;8.52591;3.50369;,
 -6.15572;2.82728;5.25816;,
 -3.77055;7.87498;2.55448;,
 -4.97819;6.38086;2.03662;,
 -7.26491;1.85309;3.48609;,
 -6.72049;3.92435;2.02090;,
 -3.77055;7.87498;2.55448;,
 -3.40298;8.11075;1.72140;,
 -4.17389;6.71179;1.10992;,
 -4.97819;6.38086;2.03662;,
 -4.97819;6.38086;2.03662;,
 -4.17389;6.71179;1.10992;,
 -6.72049;3.92435;2.02090;,
 -4.40029;5.87468;-0.03055;,
 -4.72387;5.45521;-0.34819;,
 -6.00679;4.01072;-0.15235;,
 3.38828;11.59316;2.25635;,
 3.15639;12.20576;1.80796;,
 3.08125;11.56448;2.44045;,
 2.72391;12.39523;1.52383;,
 2.10656;12.62559;2.43050;,
 2.13864;13.04426;2.06762;,
 3.15639;12.20576;1.80796;,
 3.67123;11.06096;1.15596;,
 3.42224;10.53491;0.32003;,
 2.72391;12.39523;1.52383;,
 1.48023;12.40217;2.70786;,
 1.14076;12.07050;2.17706;,
 0.09908;10.43412;3.45576;,
 -1.57508;9.63952;2.01575;,
 -1.90203;9.23912;2.88001;,
 0.09908;10.43412;3.45576;,
 -1.90203;9.23912;2.88001;,
 -0.28776;9.18190;4.64028;,
 -1.24196;8.78404;5.15739;,
 -2.39710;8.52217;5.19372;,
 -2.91730;8.38044;4.73152;,
 -3.10215;8.52591;3.50369;,
 -1.90203;9.23912;2.88001;,
 -1.57508;9.63952;2.01575;,
 -3.10215;8.52591;3.50369;,
 -2.65071;8.50471;1.16324;,
 -3.77055;7.87498;2.55448;,
 -3.40298;8.11075;1.72140;,
 3.52326;7.21191;-3.62070;,
 3.92678;6.55584;-4.33637;,
 3.42400;5.88587;-4.80980;,
 2.43075;6.47331;-3.98322;,
 5.11532;5.97339;-3.95484;,
 4.44499;6.30498;-4.39619;,
 5.23488;6.42516;-2.63410;,
 3.92678;6.55584;-4.33637;,
 3.52326;7.21191;-3.62070;,
 4.71040;7.24791;-1.90719;,
 3.61906;8.45799;-2.32187;,
 3.94271;8.48057;-1.86100;,
 -1.16894;8.39413;5.63295;,
 -1.24196;8.78404;5.15739;,
 -1.84891;7.96423;5.94025;,
 -2.39710;8.52217;5.19372;,
 -2.46251;8.12826;5.69526;,
 -2.46251;8.12826;5.69526;,
 -2.39710;8.52217;5.19372;,
 -2.91730;8.38044;4.73152;,
 -2.83872;7.69985;5.55509;,
 -1.43156;7.08842;6.09436;,
 -1.84891;7.96423;5.94025;,
 -1.75735;5.70173;6.54648;,
 -3.19754;6.36888;6.10836;,
 -2.46251;8.12826;5.69526;,
 -2.83872;7.69985;5.55509;,
 3.64823;9.29115;-1.14609;,
 3.94271;8.48057;-1.86100;,
 3.61906;8.45799;-2.32187;,
 2.13864;13.04426;2.06762;,
 2.72391;12.39523;1.52383;,
 1.14076;12.07050;2.17706;,
 3.42224;10.53491;0.32003;,
 3.64823;9.29115;-1.14609;,
 -1.57508;9.63952;2.01575;,
 3.61906;8.45799;-2.32187;,
 3.52326;7.21191;-3.62070;,
 2.43075;6.47331;-3.98322;,
 -2.65071;8.50471;1.16324;,
 -1.50637;5.32620;-3.64748;,
 -2.83782;6.46317;-1.13621;,
 5.11532;5.97339;-3.95484;,
 5.33967;4.42895;-4.91126;,
 4.63585;5.85336;-4.72122;,
 4.44499;6.30498;-4.39619;,
 -5.04898;3.22744;6.45398;,
 -4.77604;4.62089;6.09742;,
 -6.15572;2.82728;5.25816;,
 -5.62245;1.97395;6.17570;,
 3.04356;3.28797;5.59482;,
 3.07200;4.53346;5.31793;,
 1.77807;4.44380;6.12191;,
 2.45021;2.60335;5.86024;,
 -0.44296;-0.33545;-3.49710;,
 -2.14066;-0.79743;-0.08009;,
 -4.55790;-0.48272;0.35345;,
 5.65995;-0.48460;-1.52342;,
 4.64117;-0.60206;-2.89833;,
 -5.21473;-0.46440;2.38561;,
 4.87595;-0.21989;0.53377;,
 2.81127;-0.64242;0.83227;,
 1.01188;-0.01850;4.11817;,
 -4.05380;-0.37393;3.59929;,
 2.04317;-0.82813;-1.55093;,
 -1.32621;-0.65956;2.30832;,
 -1.32621;-0.65956;2.30832;;
 
 182;
 4;0,1,2,3;,
 3;4,5,6;,
 3;6,5,7;,
 3;5,8,7;,
 3;8,9,7;,
 3;9,10,7;,
 3;11,12,13;,
 3;13,12,14;,
 3;12,15,14;,
 3;15,16,14;,
 3;17,18,19;,
 3;18,20,19;,
 3;20,21,19;,
 3;21,22,19;,
 3;22,23,19;,
 3;24,25,26;,
 3;25,27,26;,
 3;27,28,26;,
 3;29,30,31;,
 3;31,30,32;,
 3;30,33,32;,
 3;33,34,32;,
 3;35,36,37;,
 3;36,38,37;,
 3;38,39,37;,
 4;40,41,42,43;,
 3;44,45,46;,
 3;45,47,46;,
 3;46,47,48;,
 3;47,49,48;,
 3;48,49,50;,
 3;49,51,50;,
 3;52,53,54;,
 3;53,55,54;,
 3;55,56,54;,
 3;56,57,54;,
 3;58,59,60;,
 3;59,61,60;,
 3;61,62,60;,
 4;63,64,65,66;,
 4;67,68,69,70;,
 3;71,72,73;,
 3;72,74,73;,
 3;74,75,73;,
 3;76,77,78;,
 3;78,77,79;,
 3;77,80,79;,
 3;80,81,79;,
 3;79,81,82;,
 3;81,83,82;,
 4;84,85,86,87;,
 3;88,89,90;,
 3;89,91,90;,
 3;91,92,90;,
 3;90,92,93;,
 3;92,94,93;,
 3;93,94,95;,
 3;94,96,95;,
 3;97,98,99;,
 3;98,100,99;,
 3;99,100,101;,
 3;100,102,101;,
 3;102,103,101;,
 3;101,103,104;,
 3;103,105,104;,
 4;106,107,108,109;,
 3;110,111,112;,
 3;111,113,112;,
 3;112,113,114;,
 3;113,115,114;,
 3;116,117,118;,
 3;118,117,119;,
 3;117,120,119;,
 3;120,121,119;,
 3;122,123,124;,
 3;123,125,124;,
 3;124,125,126;,
 3;125,127,126;,
 4;128,129,130,131;,
 3;132,133,134;,
 3;133,135,134;,
 3;134,135,136;,
 3;135,137,136;,
 3;138,139,140;,
 3;140,139,141;,
 3;141,139,142;,
 3;142,139,143;,
 3;139,144,143;,
 4;145,146,147,148;,
 4;149,150,151,152;,
 3;153,154,155;,
 3;156,157,158;,
 3;158,157,159;,
 3;159,157,160;,
 3;157,161,160;,
 3;162,163,164;,
 3;164,163,165;,
 3;163,166,165;,
 3;165,166,167;,
 3;166,168,167;,
 3;168,169,167;,
 3;167,169,170;,
 3;169,171,170;,
 4;172,173,174,175;,
 3;176,177,178;,
 3;177,179,178;,
 3;179,180,178;,
 3;180,181,178;,
 3;182,183,184;,
 3;183,185,184;,
 3;184,185,186;,
 3;185,187,186;,
 4;188,189,190,191;,
 3;192,193,194;,
 3;193,195,194;,
 3;195,196,194;,
 3;197,198,199;,
 3;199,198,200;,
 3;200,198,201;,
 3;201,198,202;,
 3;198,203,202;,
 3;204,205,206;,
 3;205,207,206;,
 3;206,207,208;,
 3;207,209,208;,
 4;210,211,212,213;,
 3;214,215,216;,
 3;215,217,216;,
 3;217,218,216;,
 3;216,218,219;,
 3;218,220,219;,
 3;220,221,219;,
 3;222,223,224;,
 3;223,225,224;,
 3;225,226,224;,
 4;227,228,229,230;,
 3;231,232,233;,
 3;233,232,234;,
 3;232,235,234;,
 3;235,236,234;,
 3;237,238,239;,
 3;240,241,242;,
 3;241,243,242;,
 3;243,244,242;,
 3;242,244,245;,
 3;244,246,245;,
 3;246,247,245;,
 3;247,248,245;,
 3;245,248,249;,
 3;248,250,249;,
 3;250,251,249;,
 4;252,253,254,255;,
 4;256,257,258,259;,
 4;260,261,262,263;,
 3;264,265,37;,
 3;265,266,37;,
 3;266,32,37;,
 3;264,37,40;,
 4;54,267,268,46;,
 4;266,269,26,32;,
 3;6,7,270;,
 3;270,7,271;,
 3;7,272,271;,
 4;54,6,270,267;,
 4;19,26,269,273;,
 3;7,14,272;,
 3;46,268,40;,
 3;268,274,40;,
 3;274,264,40;,
 3;275,273,265;,
 3;265,273,266;,
 3;273,269,266;,
 3;272,14,276;,
 3;276,14,273;,
 3;14,19,273;,
 3;267,270,268;,
 3;268,270,274;,
 3;270,271,274;,
 3;271,272,274;,
 3;274,272,264;,
 3;272,275,264;,
 3;275,265,264;;
 
 MeshMaterialList {
  11;
  182;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.440000;0.480000;0.480000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.640000;0.640000;0.640000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.640000;0.640000;0.640000;1.000000;;
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
  128;
  0.842259;-0.215364;0.494185;,
  0.993580;-0.074151;-0.085448;,
  0.955391;0.295219;0.008547;,
  0.906511;0.228297;0.355130;,
  0.558036;-0.597297;0.576049;,
  0.815561;0.092175;0.571283;,
  0.834280;0.147830;0.531153;,
  0.751165;-0.159554;-0.640542;,
  0.605626;-0.144666;0.782489;,
  0.095521;-0.586850;0.804042;,
  0.268907;0.127280;0.954719;,
  0.230731;0.239150;0.943170;,
  -0.009840;0.144344;0.989479;,
  -0.233098;-0.177548;0.956108;,
  -0.340777;0.254894;0.904931;,
  0.122877;-0.117130;0.985486;,
  0.940562;-0.101282;0.324169;,
  0.128570;-0.270626;0.954060;,
  -0.783349;-0.571009;0.245586;,
  -0.871059;0.264125;0.414118;,
  -0.776274;0.033785;0.629490;,
  -0.829896;-0.421131;-0.365952;,
  -0.879732;0.320381;-0.351322;,
  -0.845886;0.298346;-0.442117;,
  -0.792724;0.137386;-0.593897;,
  -0.541975;-0.524746;-0.656434;,
  -0.590218;0.247988;-0.768209;,
  -0.467341;-0.028433;-0.883619;,
  0.045253;-0.779412;-0.624876;,
  -0.062480;0.180568;-0.981576;,
  0.505324;-0.320299;-0.801284;,
  -0.013348;0.414963;-0.909740;,
  0.267699;0.721966;-0.638046;,
  0.491734;0.731381;-0.472524;,
  -0.613880;-0.201496;-0.763250;,
  -0.147596;0.081484;-0.985685;,
  0.848701;0.444758;-0.286177;,
  0.739423;0.605143;-0.295052;,
  0.885883;0.459333;-0.065005;,
  0.921067;0.386997;-0.043229;,
  0.876809;0.190571;0.441462;,
  0.306239;0.328648;0.893425;,
  0.238251;0.287440;0.927693;,
  0.741433;0.545783;-0.390382;,
  0.948042;0.311849;-0.062975;,
  0.902514;0.299334;0.309625;,
  0.740892;0.134060;0.658109;,
  0.766966;0.544139;-0.340112;,
  0.477007;0.727718;-0.492839;,
  0.674818;0.540916;-0.502026;,
  0.845617;0.478172;-0.237242;,
  0.747703;0.289591;0.597560;,
  0.657748;0.221417;0.719960;,
  0.469082;0.328238;0.819891;,
  0.306972;0.415110;0.856418;,
  0.483521;0.255288;0.837279;,
  0.369749;0.524077;0.767221;,
  0.547579;0.431361;0.716997;,
  -0.387767;0.689344;0.611917;,
  -0.203732;0.729901;0.652486;,
  -0.029301;0.789556;0.612978;,
  0.383868;0.482628;0.787220;,
  0.747270;0.290041;0.597883;,
  0.837112;0.540976;0.081170;,
  0.745818;0.553560;0.370577;,
  0.201415;0.480736;0.853419;,
  -0.056128;0.513821;0.856059;,
  -0.113385;0.845438;0.521898;,
  -0.466230;0.586659;-0.662164;,
  -0.269066;0.711946;-0.648641;,
  -0.641937;0.651588;-0.404165;,
  -0.553371;0.668369;-0.497055;,
  -0.591681;0.639628;-0.490703;,
  -0.527842;0.823553;0.207712;,
  -0.659720;0.713762;0.235189;,
  -0.634051;0.688222;-0.352604;,
  -0.698259;0.606175;-0.380771;,
  -0.652205;0.697026;-0.297966;,
  -0.511013;0.781218;-0.358557;,
  -0.747638;0.464887;0.474255;,
  -0.666777;0.655622;0.354355;,
  -0.684794;0.717931;0.125029;,
  -0.710123;0.702823;0.042008;,
  -0.818545;0.571364;0.059400;,
  0.519625;0.643836;0.561663;,
  -0.485915;0.819009;-0.305139;,
  -0.403778;0.875531;0.265347;,
  -0.316816;0.832308;0.454853;,
  0.182459;0.767035;-0.615115;,
  0.686578;0.526660;-0.501239;,
  -0.459971;0.568578;0.682016;,
  0.041239;-0.973338;0.225640;,
  0.022262;-0.995714;-0.089771;,
  -0.041057;-0.981724;0.185830;,
  -0.240655;-0.969823;0.039103;,
  -0.223855;-0.968395;-0.110002;,
  -0.036617;-0.998321;-0.044877;,
  0.099720;-0.983331;0.152037;,
  0.144430;-0.970545;0.192827;,
  -0.017035;-0.999685;-0.018439;,
  0.195251;-0.970492;-0.141499;,
  0.576115;-0.814670;0.066363;,
  0.368307;-0.894189;0.254512;,
  -0.376195;-0.263674;0.888230;,
  -0.857330;-0.113538;0.502090;,
  -0.827895;-0.162203;-0.536918;,
  0.466851;0.598850;-0.650714;,
  0.906602;0.259773;-0.332553;,
  0.616859;0.427655;0.660754;,
  0.427330;0.327474;0.842704;,
  -0.828496;0.390290;0.401581;,
  -0.775502;0.458188;0.434351;,
  -0.831161;0.498575;0.246158;,
  -0.727677;0.513198;0.455098;,
  -0.148722;0.703180;0.695284;,
  0.814716;0.342883;0.467622;,
  0.607164;0.580631;-0.542421;,
  -0.788267;0.601860;0.128059;,
  -0.417193;0.332466;-0.845823;,
  -0.417878;0.355115;-0.836224;,
  -0.327883;0.513767;-0.792803;,
  -0.418310;0.377550;-0.826119;,
  -0.417947;0.516513;-0.747351;,
  -0.326148;0.737457;-0.591427;,
  -0.750822;0.251729;0.610654;,
  -0.109458;-0.979943;-0.166523;,
  -0.018118;-0.978306;-0.206371;,
  -0.088475;-0.949945;0.299627;;
  182;
  4;0,1,2,3;,
  3;3,5,0;,
  3;0,5,4;,
  3;5,6,4;,
  3;6,7,7;,
  3;8,8,4;,
  3;103,10,103;,
  3;4,10,9;,
  3;10,11,9;,
  3;11,12,9;,
  3;9,12,13;,
  3;12,14,13;,
  3;14,15,13;,
  3;16,16,16;,
  3;17,17,13;,
  3;13,104,18;,
  3;104,19,18;,
  3;19,20,18;,
  3;105,22,105;,
  3;18,22,21;,
  3;22,23,21;,
  3;23,24,21;,
  3;21,24,25;,
  3;24,26,25;,
  3;26,27,25;,
  4;28,25,27,29;,
  3;28,29,30;,
  3;29,31,30;,
  3;30,31,35;,
  3;31,32,35;,
  3;35,34,34;,
  3;32,33,106;,
  3;30,107,1;,
  3;107,36,1;,
  3;36,37,1;,
  3;37,2,1;,
  3;2,38,3;,
  3;38,39,3;,
  3;39,40,3;,
  4;12,11,41,42;,
  4;2,37,43,38;,
  3;39,44,40;,
  3;44,45,40;,
  3;45,46,40;,
  3;43,47,38;,
  3;38,47,39;,
  3;47,48,39;,
  3;48,49,39;,
  3;39,49,44;,
  3;49,50,44;,
  4;51,5,3,40;,
  3;5,51,108;,
  3;51,52,6;,
  3;52,53,6;,
  3;6,53,10;,
  3;53,54,10;,
  3;10,54,11;,
  3;54,41,11;,
  3;55,56,53;,
  3;56,57,53;,
  3;53,57,54;,
  3;57,58,54;,
  3;58,59,54;,
  3;54,59,61;,
  3;59,60,61;,
  4;46,52,51,40;,
  3;44,50,45;,
  3;50,63,45;,
  3;45,63,62;,
  3;63,64,62;,
  3;45,62,46;,
  3;46,62,52;,
  3;62,55,52;,
  3;55,53,52;,
  3;54,61,41;,
  3;61,65,41;,
  3;41,65,42;,
  3;65,66,42;,
  4;61,60,67,65;,
  3;69,31,68;,
  3;31,29,68;,
  3;68,29,26;,
  3;29,27,26;,
  3;72,68,71;,
  3;71,68,70;,
  3;70,68,23;,
  3;23,68,24;,
  3;68,26,24;,
  4;109,56,55,62;,
  4;73,74,58,73;,
  3;75,71,70;,
  3;78,72,77;,
  3;77,72,76;,
  3;76,72,75;,
  3;72,71,75;,
  3;79,80,110;,
  3;14,80,111;,
  3;80,81,111;,
  3;111,81,19;,
  3;81,82,19;,
  3;82,83,19;,
  3;19,83,112;,
  3;83,113,20;,
  4;82,77,76,83;,
  3;83,76,22;,
  3;76,75,22;,
  3;75,70,22;,
  3;70,23,22;,
  3;64,63,56;,
  3;114,84,56;,
  3;56,84,57;,
  3;84,115,57;,
  4;63,50,49,116;,
  3;58,74,117;,
  3;74,85,59;,
  3;85,86,59;,
  3;59,86,60;,
  3;60,86,67;,
  3;67,86,87;,
  3;87,86,80;,
  3;86,81,80;,
  3;86,85,81;,
  3;85,78,81;,
  3;81,78,82;,
  3;78,77,82;,
  4;88,32,31,69;,
  3;36,33,37;,
  3;33,32,37;,
  3;32,88,37;,
  3;37,88,43;,
  3;88,89,43;,
  3;89,47,43;,
  3;65,67,66;,
  3;67,87,66;,
  3;87,90,66;,
  4;90,87,80,79;,
  3;42,66,12;,
  3;12,66,14;,
  3;66,90,14;,
  3;90,79,14;,
  3;48,47,89;,
  3;118,119,120;,
  3;119,121,120;,
  3;49,48,120;,
  3;120,122,85;,
  3;48,123,85;,
  3;123,88,85;,
  3;88,69,85;,
  3;85,69,78;,
  3;69,68,78;,
  3;68,72,78;,
  4;36,107,106,33;,
  4;124,111,19,104;,
  4;8,6,10,8;,
  3;92,96,125;,
  3;96,95,125;,
  3;95,21,25;,
  3;92,25,126;,
  4;1,101,100,30;,
  4;95,94,18,21;,
  3;0,4,102;,
  3;102,4,98;,
  3;4,91,98;,
  4;1,0,102,101;,
  4;127,18,94,93;,
  3;4,9,91;,
  3;30,100,28;,
  3;100,99,28;,
  3;99,92,28;,
  3;97,93,96;,
  3;96,93,95;,
  3;93,94,95;,
  3;91,9,97;,
  3;97,9,93;,
  3;9,127,93;,
  3;101,102,100;,
  3;100,102,99;,
  3;102,98,99;,
  3;98,91,99;,
  3;99,91,92;,
  3;91,97,92;,
  3;97,96,92;;
 }
 MeshTextureCoords {
  277;
  0.507991;0.524120;,
  0.383278;0.500029;,
  0.407176;0.693838;,
  0.507991;0.700690;,
  0.603749;0.818252;,
  0.564944;0.817314;,
  0.603749;0.994737;,
  0.475047;0.985966;,
  0.494583;0.874654;,
  0.498657;0.920646;,
  0.470812;0.943678;,
  0.132935;0.548736;,
  0.110861;0.478578;,
  0.132935;0.589903;,
  0.005252;0.614382;,
  0.062652;0.422955;,
  0.016213;0.423602;,
  0.716459;0.994737;,
  0.716458;0.803040;,
  0.615583;0.985554;,
  0.670525;0.801893;,
  0.637314;0.856732;,
  0.633121;0.916520;,
  0.614252;0.944713;,
  0.795769;0.725110;,
  0.754524;0.721507;,
  0.795769;0.819650;,
  0.726962;0.755809;,
  0.760152;0.818852;,
  0.445141;0.156426;,
  0.383298;0.180390;,
  0.480574;0.158786;,
  0.480574;0.284598;,
  0.383278;0.269290;,
  0.404809;0.287121;,
  0.821983;0.830177;,
  0.746211;0.832166;,
  0.821983;0.994737;,
  0.726962;0.953100;,
  0.808794;0.994732;,
  0.947473;0.991535;,
  0.947473;0.875084;,
  0.934245;0.875324;,
  0.907974;0.994737;,
  0.625148;0.516385;,
  0.625148;0.478277;,
  0.518495;0.527412;,
  0.571549;0.326901;,
  0.528193;0.398386;,
  0.559768;0.326438;,
  0.553289;0.338805;,
  0.553248;0.332574;,
  0.203214;0.288384;,
  0.212535;0.417286;,
  0.306648;0.298475;,
  0.241593;0.478648;,
  0.260342;0.490257;,
  0.306648;0.493992;,
  0.005252;0.109050;,
  0.017875;0.153905;,
  0.106561;0.115462;,
  0.046779;0.224828;,
  0.106561;0.189490;,
  0.317152;0.356734;,
  0.363457;0.354531;,
  0.363457;0.295018;,
  0.325018;0.316603;,
  0.376374;0.716576;,
  0.329913;0.712831;,
  0.349780;0.762928;,
  0.376374;0.763833;,
  0.841532;0.434220;,
  0.875028;0.523508;,
  0.901007;0.395846;,
  0.896025;0.527412;,
  0.901007;0.500299;,
  0.153260;0.210687;,
  0.119981;0.266454;,
  0.178423;0.219353;,
  0.178423;0.297527;,
  0.127053;0.332040;,
  0.134674;0.352245;,
  0.170627;0.392599;,
  0.152652;0.412428;,
  0.005252;0.029558;,
  0.006026;0.092414;,
  0.044513;0.098523;,
  0.044513;0.024252;,
  0.652893;0.649225;,
  0.652384;0.586415;,
  0.578666;0.700690;,
  0.652893;0.545987;,
  0.640359;0.537939;,
  0.539239;0.688821;,
  0.571517;0.539538;,
  0.518495;0.617583;,
  0.540716;0.562422;,
  0.722511;0.371397;,
  0.711389;0.340368;,
  0.722511;0.483856;,
  0.662678;0.315537;,
  0.669544;0.527412;,
  0.657726;0.321687;,
  0.640860;0.385355;,
  0.647615;0.519538;,
  0.635652;0.468951;,
  0.935057;0.584526;,
  0.888746;0.659506;,
  0.897191;0.700690;,
  0.935057;0.688984;,
  0.959744;0.925383;,
  0.957977;0.952250;,
  0.981123;0.925383;,
  0.983896;0.994737;,
  0.987997;0.945037;,
  0.989618;0.959010;,
  0.939196;0.198568;,
  0.953193;0.213963;,
  0.931163;0.172201;,
  0.941149;0.084586;,
  0.956069;0.196141;,
  0.956069;0.083570;,
  0.445544;0.145899;,
  0.468833;0.144571;,
  0.441027;0.106838;,
  0.492617;0.122772;,
  0.456926;0.065568;,
  0.492617;0.094289;,
  0.977689;0.593355;,
  0.977689;0.540459;,
  0.954670;0.563592;,
  0.945561;0.595976;,
  0.203214;0.696757;,
  0.230334;0.700690;,
  0.229631;0.530962;,
  0.372774;0.625505;,
  0.267363;0.504518;,
  0.358821;0.504518;,
  0.663397;0.651648;,
  0.741138;0.700690;,
  0.689857;0.596252;,
  0.687480;0.592538;,
  0.761609;0.555985;,
  0.786067;0.568667;,
  0.786067;0.691160;,
  0.494599;0.195527;,
  0.499619;0.198985;,
  0.499619;0.166009;,
  0.491078;0.181908;,
  0.279664;0.095297;,
  0.270529;0.112021;,
  0.276924;0.124223;,
  0.279664;0.116811;,
  0.505949;0.507570;,
  0.505949;0.483687;,
  0.497045;0.495243;,
  0.897470;0.994737;,
  0.897470;0.842665;,
  0.866668;0.962728;,
  0.832487;0.880506;,
  0.832539;0.833348;,
  0.838860;0.828542;,
  0.305907;0.747491;,
  0.272950;0.714084;,
  0.319409;0.811101;,
  0.319409;0.874998;,
  0.245792;0.711216;,
  0.286013;0.949779;,
  0.219199;0.741800;,
  0.203214;0.824435;,
  0.231299;0.994737;,
  0.205543;0.934627;,
  0.624895;0.077138;,
  0.597212;0.056681;,
  0.589960;0.145544;,
  0.624895;0.161120;,
  0.754966;0.193501;,
  0.788063;0.213963;,
  0.733015;0.084128;,
  0.817570;0.175293;,
  0.821190;0.175703;,
  0.821190;0.092904;,
  0.543093;0.006276;,
  0.520708;0.034667;,
  0.544450;0.012227;,
  0.518495;0.058692;,
  0.544450;0.066998;,
  0.523203;0.063914;,
  0.967739;0.756888;,
  0.958822;0.805879;,
  0.981851;0.864558;,
  0.981851;0.737340;,
  0.172898;0.610772;,
  0.185779;0.614382;,
  0.143439;0.551886;,
  0.185779;0.450378;,
  0.160816;0.438091;,
  0.364781;0.120681;,
  0.301187;0.214148;,
  0.371687;0.201165;,
  0.371687;0.233057;,
  0.347774;0.277857;,
  0.329344;0.277152;,
  0.304404;0.266355;,
  0.617529;0.763802;,
  0.623220;0.790772;,
  0.631889;0.713600;,
  0.644440;0.781825;,
  0.673281;0.712789;,
  0.673281;0.748131;,
  0.817585;0.819650;,
  0.817585;0.776816;,
  0.806273;0.779776;,
  0.808839;0.807456;,
  0.360351;0.369134;,
  0.327727;0.367261;,
  0.371758;0.387057;,
  0.322622;0.374120;,
  0.317152;0.415531;,
  0.371758;0.440599;,
  0.325380;0.484434;,
  0.339189;0.493992;,
  0.941278;0.051048;,
  0.966686;0.073043;,
  0.931163;0.024430;,
  0.966686;0.021573;,
  0.942751;0.011459;,
  0.702815;0.110999;,
  0.703086;0.137029;,
  0.719162;0.146460;,
  0.719162;0.098310;,
  0.912489;0.484057;,
  0.923154;0.527412;,
  0.911511;0.443885;,
  0.957607;0.443885;,
  0.940451;0.527166;,
  0.947208;0.508423;,
  0.502366;0.209511;,
  0.491078;0.274598;,
  0.502366;0.287121;,
  0.166044;0.994737;,
  0.172389;0.991723;,
  0.148065;0.989546;,
  0.190773;0.868613;,
  0.192710;0.847369;,
  0.026545;0.881075;,
  0.192710;0.769991;,
  0.181067;0.699635;,
  0.177751;0.684886;,
  0.011750;0.863493;,
  0.022834;0.624908;,
  0.005252;0.711344;,
  0.716154;0.790772;,
  0.716154;0.722762;,
  0.684171;0.779218;,
  0.683785;0.785760;,
  0.928521;0.325816;,
  0.968218;0.370983;,
  0.968218;0.288988;,
  0.924333;0.291335;,
  0.837003;0.023748;,
  0.831693;0.069830;,
  0.871020;0.082057;,
  0.871020;0.008126;,
  0.668736;0.751618;,
  0.646149;0.686682;,
  0.575236;0.510383;,
  0.398659;0.396516;,
  0.466163;0.469289;,
  0.682566;0.699029;,
  0.512714;0.676584;,
  0.468999;0.573575;,
  0.504936;0.782174;,
  0.626978;0.741899;,
  0.530231;0.561896;,
  0.581878;0.698582;,
  0.581878;0.698583;;
 }
}