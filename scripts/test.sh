# Our generic download program!

ARGS="$#"
if (( !"$ARGS" )); then
  ARGS="cmake gtest libcddb mpg123"
fi

while (( "$#" )); do
  PACKAGE=$1

  echo $1
  shift
done