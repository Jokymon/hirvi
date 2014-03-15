import os
import generate_build_tag

if os.name=="nt":
    tools_parts = ("i386-elf-", ".exe")
else:
    tools_parts = ("", "")

allflags = ""
asflags = "%s -c" % allflags
cflags = "%s -nostdinc -fvisibility=default -fno-builtin -fno-stack-protector -fno-asynchronous-unwind-tables " % allflags
ldflags = "-nostdlib"

asm = "%sgcc%s" % tools_parts
gcc = "%sgcc%s" % tools_parts
cpp = "%scpp%s" % tools_parts
ld  = "%sld%s" % tools_parts
objcopy = "%sobjcopy%s" % tools_parts
objdump = "%sobjdump%s" % tools_parts

env = Environment(
    AS = asm,
    ASFLAGS = asflags,

    CC = gcc,
    CCFLAGS = cflags,
    
    LINK = ld,
    LINKFLAGS = ldflags,

    tools = ['mingw'],

    ENV = { 'PATH' : os.environ['PATH'] }
)

srcs = []
static_libs = []

srcs.append("k_entry.S")
srcs += Glob('*.c')

generate_build_tag.create_tag_file()

kernel = env.Program('kernel.elf', srcs,
                       LIBS=static_libs,
                       LINKFLAGS="-T kernel.ld -Map kernel.map")

env.Command('kernel.lst',
            kernel,
            "%s -S -mi386 -Maddr16,data16,intel $SOURCE > $TARGET" % objdump)
