# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.testSFML.Debug:
/Users/davidscovel/FinalProject-LunarLander/DavidDalton/Xcode/Debug/testSFML:\
	/Library/Frameworks/./sfml-graphics.framework/Versions/2.5.1/sfml-graphics\
	/Library/Frameworks/./sfml-window.framework/Versions/2.5.1/sfml-window\
	/Library/Frameworks/./sfml-system.framework/Versions/2.5.1/sfml-system
	/bin/rm -f /Users/davidscovel/FinalProject-LunarLander/DavidDalton/Xcode/Debug/testSFML


PostBuild.testSFML.Release:
/Users/davidscovel/FinalProject-LunarLander/DavidDalton/Xcode/Release/testSFML:\
	/Library/Frameworks/./sfml-graphics.framework/Versions/2.5.1/sfml-graphics\
	/Library/Frameworks/./sfml-window.framework/Versions/2.5.1/sfml-window\
	/Library/Frameworks/./sfml-system.framework/Versions/2.5.1/sfml-system
	/bin/rm -f /Users/davidscovel/FinalProject-LunarLander/DavidDalton/Xcode/Release/testSFML


PostBuild.testSFML.MinSizeRel:
/Users/davidscovel/FinalProject-LunarLander/DavidDalton/Xcode/MinSizeRel/testSFML:\
	/Library/Frameworks/./sfml-graphics.framework/Versions/2.5.1/sfml-graphics\
	/Library/Frameworks/./sfml-window.framework/Versions/2.5.1/sfml-window\
	/Library/Frameworks/./sfml-system.framework/Versions/2.5.1/sfml-system
	/bin/rm -f /Users/davidscovel/FinalProject-LunarLander/DavidDalton/Xcode/MinSizeRel/testSFML


PostBuild.testSFML.RelWithDebInfo:
/Users/davidscovel/FinalProject-LunarLander/DavidDalton/Xcode/RelWithDebInfo/testSFML:\
	/Library/Frameworks/./sfml-graphics.framework/Versions/2.5.1/sfml-graphics\
	/Library/Frameworks/./sfml-window.framework/Versions/2.5.1/sfml-window\
	/Library/Frameworks/./sfml-system.framework/Versions/2.5.1/sfml-system
	/bin/rm -f /Users/davidscovel/FinalProject-LunarLander/DavidDalton/Xcode/RelWithDebInfo/testSFML




# For each target create a dummy ruleso the target does not have to exist
/Library/Frameworks/./sfml-graphics.framework/Versions/2.5.1/sfml-graphics:
/Library/Frameworks/./sfml-system.framework/Versions/2.5.1/sfml-system:
/Library/Frameworks/./sfml-window.framework/Versions/2.5.1/sfml-window:
