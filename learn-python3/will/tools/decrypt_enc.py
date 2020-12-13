#!/nfs/software/LithoTuner/4.7.0/release/LSF/r4.7.0/bin/tachyon_python


import os
import sys
from lxml import etree


def is_xml(f):
    try:
        etree.parse(f)
    except Exception as e:
        return False
    else:
        return True

def main() :
    enc_files = sys.argv[1:]
    for enc_file in enc_files:
        output_file = enc_file.replace("enc", "xml")
        cmd = "/gpfs/software/LithoTuner/4.2.0/rc4/LSF/r4.2.0rc4/bin/decrypt -xf %s %s" %(enc_file, output_file)
        os.system(cmd)
        if not os.path.exists(output_file):
            sys.stderr.write("---Warning: decrypt '{}' fail\n".format(enc_file))
        else:
            if not is_xml(output_file):
                output_file_new = output_file.replace('xml', 'txt')
                os.rename(output_file, output_file_new)
                output_file = output_file_new
            print("---decrypt to '{}'".format(output_file))

if __name__ == '__main__':
   main()
