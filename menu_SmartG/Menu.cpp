#include "Menu.h"

 MenuItem::MenuItem (const char* text,fptr callback):
  
  text(text),
  callback(callback)
  
  {


}

  const char* MenuItem::getText(){
    
       return text;

  }


  fptr MenuItem::getcallback(){
   
   return callback;

  }


Menu::Menu(){
 index = 0;
  n_items = 0;
  MenuStream = NULL;
}

void Menu::begin(Stream &s)
{
  MenuStream = &s;
}



void Menu::addItem(const char* text,fptr callback){

if(n_items < 10)
  items[n_items] = new MenuItem(text,callback);
   n_items++;
}

void Menu::up(){

  if(index < n_items-1){
     index++;
 MenuStream->println(items[index]->getText());

  }
}

void Menu::down(){

  if(index > 0){
    index--;
  MenuStream->println(items[index]->getText());
  
  }
}

void Menu::enter(){

  fptr callback = items[index]-> getcallback();
  if(callback != NULL) callback();

}

