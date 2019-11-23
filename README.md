# UE4: Rearranged ChildComponents
*UE4 C++ - Restores the previous arrangement of child components after loading*

If your code is based on the arrangement of child components, you are lost! The child components are reordered every time you save and reload a project:

![UE4 Components will be reordered](images\UE4 Component reordered.gif)

This project shows a simple solution for recreating the previous arrangement after reloading a project. The [background](BACKGROUND.md) of this project is a project, which extensively uses the arrangement order of child components, because the arrangement determines the location, rotation and scaling of each child component.

