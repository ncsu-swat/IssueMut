THISDIR=`dirname "$(realpath "$0")"`
LANGCHAIN_ISSUEMUT=$THISDIR
export PYTHONPATH=${LANGCHAIN_ISSUEMUT}:$PYTHONPATH

export GOOGLE_API_KEY=""

mkdir -p ${THISDIR}/bin ${THISDIR}/../results ${THISDIR}/../results/diff ${THISDIR}/../results/mutators ${THISDIR}/../results/mutators/wrong ${THISDIR}/../results/mutators/errors ${THISDIR}/../results/mutators/all ${THISDIR}/../results/mutators/correct ${THISDIR}/../results/temp

OS="$(uname)"
if [[ "$OS" == "Linux" ]]; then
    ln -sf "$(which gsed)" "${THISDIR}/bin/sed" >/dev/null 2>&1
elif [[ "$OS" == "Darwin" ]]; then
    if ! command -v gsed >/dev/null 2>&1; then
        echo "Installing gsed using brew..."
        brew install gsed
    fi
    ln -s "$(which gsed)" "${THISDIR}/bin/sed"
fi

source venv/bin/activate

# run the example
export PATH="${THISDIR}/bin:$PATH"
python ${LANGCHAIN_ISSUEMUT}/main_parallel.py
