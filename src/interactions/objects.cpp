void createToilet(){
    Interact_Object toilet;
    toilet.objectName = "Toilet";
    toilet.objectTexture = "toilet_texture.png";
    toilet.x = 100; // Example position
    toilet.y = 200; // Example position
    toilet.width = 50; // Example size
    toilet.height = 50; // Example size
    toilet.timesUsed = 0;
    toilet.eventFunc = []() {
        // Define the event handling logic here
        std::cout << "Standing in toilet" << std::endl;
    };
}