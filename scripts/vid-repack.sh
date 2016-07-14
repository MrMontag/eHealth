# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Copyright (C)    2016  Alexander (MrMontag) Fust <MrMontagOpenDev@gmail.com>
#
# This script creates mp4 files for all h264 videos contained in a folder
# and it's subdirectories. To run the processing the Open Source multimedia
# framework GPAC <https://gpac.wp.mines-telecom.fr/> is needed. If it is not
# yet installed please run the following commands (for Debian based systems).
#
#     sudo apt-get update
#     sudo apt-get install gpac
#
#!/bin/bash
    
find -printf "%p\n" | grep -i -e ".*\.h264$" | while read -r fp
do
    echo "$fp"
    MP4Box -add $fp ${fp/h264/mp4}
    echo ""
done
