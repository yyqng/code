#!/usr/bin/env python
import lxml.etree as etree
import os
import sys


def pretty(xml_file):
    if not os.path.exists(xml_file):
        sys.stderr.write("'{}' not exists\n".format(xml_file))
        return -1

    target_dir = os.path.dirname(xml_file)
    new_name = 'pretty_{}'.format(os.path.basename(xml_file))
    pretty_path = os.path.join(target_dir, new_name)
    if os.path.exists(pretty_path):
        sys.stderr.write("{} already exists, quit\n".format(pretty_path))
        return -1

    et = etree.parse(xml_file)
    content = etree.tostring(et, pretty_print=True)

    with open(pretty_path, 'w') as f:
        f.write(content)
    print("Save to: {}".format(pretty_path))
    return 0


def main():
    if len(sys.argv) != 2:
        sys.stderr.write("Need input xml file\n")
        return -1
    return pretty(sys.argv[1])

if __name__ == '__main__':
    main()
