

if [ ! "$#" ]; then
  $@="foo bar baz"
fi

echo "here1 $@"

while (( "$#" )); do
  echo "here: $1"
  shift
done


# echo "Testing \"0\""
# if [ ! "" ]      # zero
# then
#   echo "0 is true."
# else          # Or else ...
#   echo "0 is false."
# fi            # 0 is true.