
(\
 cd $ROOT/rec &&\
 make -s &&\
 "$ROOT/rec/scripts/makeProtoFiles.sh" &&\
 "$ROOT/rec/scripts/makeProjectFiles.sh" &&\
 "$ROOT/rec/scripts/makeEmacsTags.sh"\
)

