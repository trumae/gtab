echo "Removendo velho diretorio de release"
rm -rf releasepack

echo "Criando diretorio para build"
mkdir releasepack

echo "Rodando cmake"
cd releasepack
cmake -DCMAKE_BUILD_TYPE=Release ..

echo "Compilando"
make -j 4
cd ..

echo "Criando tgz"
rm -rf packtmp
rm pack.tgz

mkdir packtmp
cd packtmp
cp ../releasepack/src/gtab .
cp -R ../www .
tar zvfc ../gtab.tgz *

echo "Removendo lixo"
cd ..
rm -rf packtmp
rm -rf releasepack

