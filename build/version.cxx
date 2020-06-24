int version()
{
   // Reads from the file build/version_number the new version
   // number and generates the header base/inc/RVersion.h.
   // To be executed as CINT script by build/unix/makeversion.sh.
   //
   // Author: Fons Rademakers   11/10/99

   const char *in  = "build/version_number";

   FILE *fp = fopen(in, "r");
   if (!fp) {
      printf("version.cxx: can not open input file %s\n", in);
      return 1;
   }
   char vers[32];
   fgets(vers, sizeof(vers), fp);
   if (vers[strlen(vers)-1] == '\n') vers[strlen(vers)-1] = 0;
   fclose(fp);

   const char *out = "core/base/inc/RVersion.h";
   fp = fopen(out, "w");
   if (!fp) {
      printf("version.cxx: can not open output file %s\n", out);
      return 1;
   }

   fprintf(fp, "#ifndef ROOT_RVersion\n");
   fprintf(fp, "#define ROOT_RVersion\n\n");
   fprintf(fp, "/* Version information automatically generated by installer. */\n\n");
   fprintf(fp, "/*\n");
   fprintf(fp, " * These macros can be used in the following way:\n");
   fprintf(fp, " *\n");
   fprintf(fp, " *    #if ROOT_VERSION_CODE >= ROOT_VERSION(2,23,4)\n");
   fprintf(fp, " *       #include <newheader.h>\n");
   fprintf(fp, " *    #else\n");
   fprintf(fp, " *       #include <oldheader.h>\n");
   fprintf(fp, " *    #endif\n");
   fprintf(fp, " *\n");
   fprintf(fp, "*/\n\n");

   int xx, yy, zz;
   sscanf(vers, "%d.%d/%d", &xx, &yy, &zz);
   int vers_code = (xx << 16) + (yy << 8) + zz;

   fprintf(fp, "#define ROOT_RELEASE \"%s\"\n", vers);
   fprintf(fp, "#define ROOT_RELEASE_DATE \"%s\"\n", __DATE__);
   fprintf(fp, "#define ROOT_RELEASE_TIME \"%s\"\n", __TIME__);
   fprintf(fp, "#define ROOT_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))\n");
   fprintf(fp, "#define ROOT_VERSION_CODE ROOT_VERSION(%d,%d,%d) /* %d */\n",
           xx, yy, zz, vers_code);
   fprintf(fp, "\n#endif\n");

   fclose(fp);

   return 0;
}