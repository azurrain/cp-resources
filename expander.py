#!/usr/bin/env python3

import re
import argparse
from pathlib import Path
from typing import List


class Expander:
    guard = re.compile(r"#.*CPLIB_[A-Z0-9_]*_HPP")
    cplinclude = re.compile(r'#include\s*["<](cplib/[a-z0-9_]*(|.hpp))[">]\s*')
    nsstart = re.compile(r"\s*namespace\s*cplib\s*\{\s*")
    nsend = re.compile(r"\s*\}\s*//\s*namespace\s*cplib")
    localdef = re.compile(r"#ifdef\s*LOCAL\s*")
    endif = re.compile(r"#endif\s*")
    emptyln = re.compile(r"^$")
    included = []
    head = []
    result = []
    include = re.compile(r'#include\s*["<].*[">]\s*')
    tpalias = re.compile(r"using\s*[A-Za-z0-9_]*\s*=\s*[A-Za-z0-9_ ]*;")

    def __init__(self, libpaths: List[Path], expandns: bool) -> None:
        self.libpaths = libpaths
        self.expandns = expandns

    def findcplfile(self, filename: str) -> Path:
        for libpath in self.libpaths:
            path = libpath / filename
            if path.exists():
                return path
        raise FileNotFoundError()

    def expandcpl(self, filename: Path, filepath: Path) -> List[str]:
        if filename in self.included:
            return []
        with open(str(filepath)) as f:
            filesource = f.read()
        lines = filesource.splitlines()

        content = []
        i = 0
        j = len(lines) - 1
        while i != len(lines) and not self.nsstart.match(lines[i]):
            m = self.cplinclude.match(lines[i])
            if m:
                name = m.group(1)
                path = self.findcplfile(name)
                content.extend(self.expandcpl(name, path))
            elif not self.guard.match(lines[i]) and not self.emptyln.match(lines[i]):
                if lines[i] not in self.head:
                    self.head.append(lines[i])
            i += 1

        if filename in self.included:
            return []

        while j != -1 and not self.nsend.match(lines[j]):
            j -= 1

        self.included.append(filename)
        assert i != len(lines) and j != -1, r"namespace cplib {...} not found"

        i += 1
        j -= 1
        while self.emptyln.match(lines[i]):
            i += 1
        while self.emptyln.match(lines[j]):
            j -= 1

        if len(self.included) >= 2:
            content.append("")
        while i <= j:
            content.append(lines[i])
            i += 1
        return content

    def complete_head(self, ipos: int, tpos: int) -> None:
        for line in self.head:
            if self.tpalias.match(line) and line not in self.result:
                self.result.insert(tpos + 1, line)
                tpos += 1

        # TODO
        uns = re.compile(r"using\s*namespace\s*std;\s*")
        found = False
        for line in self.result:
            if uns.match(line):
                found = True
                break
        if not found:
            self.result.insert(ipos + 1, "using namespace std;")
            self.result.insert(ipos + 1, "")

        for line in self.head:
            if self.include.match(line) and line not in self.result:
                self.result.insert(ipos + 1, line)
                ipos += 1

    def expand(self, source: str) -> str:
        self.included = []
        self.head = []
        self.result = []
        ipos = -1
        tpos = -1
        in_localdef = False
        expanding = False
        for i, line in enumerate(source.splitlines()):
            if not in_localdef:
                in_localdef = self.localdef.match(line)
            else:
                in_localdef = not self.endif.match(line)

            if not in_localdef:
                m = self.cplinclude.match(line)
                if m:
                    filename = m.group(1)
                    filepath = self.findcplfile(filename)

                    if self.expandns:
                        if not expanding:
                            self.result.append("namespace cplib {")
                            self.result.append("")
                        expanding = True

                    self.result.extend(self.expandcpl(filename, filepath))
                    continue
                else:
                    if expanding:
                        self.result.append("")
                        self.result.append("}  // namespace cplib")
                    expanding = False

                    if self.include.match(line):
                        ipos = i
                    if self.tpalias.match(line):
                        tpos = i

            # TODO
            if not self.expandns:
                if line == "using namespace cplib;":
                    continue
                line = line.replace("cplib::", "")
            self.result.append(line)

        if expanding:
            self.result.append("")
            self.result.append("}  // namespace cplib")
            expanding = False
        self.complete_head(ipos, tpos)
        return "\n".join(self.result) + "\n"


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Expander")
    parser.add_argument("source", help="Source File")
    parser.add_argument("--lib", help="Path to cplib")
    parser.add_argument("-o", "--output", help="Output File")
    parser.add_argument("-c", "--console", action="store_true", help="Print to Console")
    parser.add_argument("-g", action="store_true", help="Expand with out namespace")
    args = parser.parse_args()

    libpaths = []
    if args.lib:
        libpaths.append(Path(args.lib))
    libpaths.append(Path.cwd())

    expander = Expander(libpaths, not bool(args.g))

    with open(args.source) as f:
        source = f.read()
    output = expander.expand(source)
    if args.console:
        print(output)
    else:
        with open(args.output if args.output else args.source, "w") as f:
            f.write(output)
