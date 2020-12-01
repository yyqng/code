import sys, os
import base64
from lxml import etree

RELEASE = "/nfs/software/LithoTuner/4.8.0/release/LSF/r4.8.0/"
def _init():
    sys.path.append(os.path.join(RELEASE, 'app'))

    import globals
    class dummy(object):
        @staticmethod
        def debug(msg):
            pass
    globals.logger = dummy
    globals.tmpdir = '/tmp'
    globals.bindir = os.path.join(RELEASE, 'bin')

def decrypt_scf(scf):
    from shared import LTUtility
    from shared import license
    if not license.haveInternalLicense():
        raise SystemExit("Need internal License")
    dc = base64.b64decode(scf)
    decode_content = LTUtility.decryptString(dc)
    print("===result:")
    print(decode_content)

def main():
    if len(sys.argv) != 2:
        raise SystemExit('Usage: <machine.xml>')
    machine_xml = sys.argv[1]
    tree = etree.parse(machine_xml)
    scf = tree.find('scf_raw_file_content')
    if scf.text is not None:
        _init()
        decrypt_scf(scf.text)
    else:
        raise SystemExit('No scf content in "{}"'.format(machine_xml))

if __name__ == '__main__':
    main()