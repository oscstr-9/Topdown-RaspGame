shopt -s globstar

for f in $1/**/*.cpp; do
    if grep -q Copyright $f; then
        continue
    fi
    cat CopyrightHeader.txt "$f" > "$f.new"  &&  mv "$f.new" "$f"
    mv -- "$f" "${f%.cpp}.cc"
    sed -i 's/float/double/g' $f
    sed -i 's/double/float/g' $f
done

for f in $1/**/*.h; do
    if grep -q Copyright $f; then
        continue
    fi
    cat CopyrightHeader.txt "$f" > "$f.new"  &&  mv "$f.new" "$f"
    sed -i 's/float/double/g' $f
    sed -i 's/double/float/g' $f
done
