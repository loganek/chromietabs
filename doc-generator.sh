#!/bin/sh

if [ "$#" -ne 1 ]; then
    echo "Expected build directory"
    exit 1
fi

tag=$(git describe --exact-match --tags HEAD)

if [ $? -ne 0 ]; then
    tag=master
fi

build_path=`cd "$1"; pwd`

prev_dir=`pwd`
cd $build_path
make documentation

git clone https://github.com/loganek/chromietabs chromietabs-tmp
cd chromietabs-tmp
git checkout gh-pages
rm $tag -rf
mkdir $tag
cp ../docs/references/html/* $tag/ -r

echo '<html><head><title>chromietabs documentation</title></head><body><ul>' > index.html

for d in */ ; do
    echo "<li><a href='$d/index.html'>$d</a>" >> index.html
done
echo '</ul></body></html>' >> index.html

git add .
git commit -m"update documentation for $tag"
git push origin gh-pages
cd ..
rm -rf chromietabs-tmp
cd $prev_dir
