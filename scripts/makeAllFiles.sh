(\
 cd $ROOT/rec &&\
 make -s &&\
 source "scripts/makeProtoFiles.sh" &&\
 "$ROOT/rec/scripts/makeProjectFiles.sh" &&\
 "$ROOT/rec/scripts/makeEmacsTags.sh"\
)
