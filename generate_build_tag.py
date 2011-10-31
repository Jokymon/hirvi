import time

tag_file = open("build_tag.h", "w")
tag_file.write("#ifndef _BUILD_TAG_H\n")
tag_file.write("#define _BUILD_TAG_H\n\n")

tag_file.write("#define BUILDTAG \"%s\"\n\n" % time.strftime("%Y%m%d-%H%M"))

tag_file.write("#endif\n")
