echo "for:"
for((i=0; i<3; ++i))
{
    echo $i
}

i=0
echo "while:"
while ((i<3))
do
    echo $i
    ((++i))
done

i=0
echo "until:"
until ((i>=3))
do
    echo $i
    ((++i))
done
