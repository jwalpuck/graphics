 //Initialize values of temp
      for(i = 0, j = 0, k = 4; j < 16; i++, j++, k--) { // BAM: modified to make j counter
	if(k == 0) {
	  i += 4;
	  k = 4;
	}
	//printf("i, j, k %d %d %d\n", i, j, k); // something is wrong here
	temp[i] = b->control[j];
      }

      for(i = 0; i < 4; i++) { 
	//Create a temporary vertical array to pass to deCast
	for(j = 0, k = i; j < 4; j++, k += 8) {
	  vertTemp[j] = temp[k];
	}
	deCastAlg(&(vertTemp[0]));

	//Copy the points back
	for(j = i * 8, k = 0; k < 8; j++, k++) {
	  temp[j] = vertTemp[k];
 	}
      }

      //Make space in horiz array
      for(i = 0, j = 0, k = 4; j < 32; i++, j++, k--) { // BAM: modified to make j counter
      	if(k == 0) {
      	  i += 4;
      	  k = 4;
      	}
	//printf("i, j, k %d %d %d\n", i, j, k); // something is wrong here
      	temp2[i] = temp[j];
      }

      //DeCast for the rest of the points
      for(i = 0; i < 8; i++) {
      	deCastAlg(&(temp2[i * 8]));
      }

      //We may not need this step
      /* int idx = 0; */
      /* for( i = 0; i<8; i++){ */
      /* 	for(j = i; j < 64; j+=8) { */
      /* 	  temp3[idx++] = temp2[j]; */
      /* 	} */
      /* 	printf("%\n"); */
      /* } */

      int bez1c = 0;
      int bez2c = 0;
      int bez3c = 0;
      int bez4c = 0;
      
      //Split up points into respective quadrants
      for(i = 0; i < 64; i++) {
	if((i / 4) % 2 == 0 && i < 32) {
	  bez1[bez1c] = temp2[i];
	  bez1c++;
	}
	if((i / 4) % 2 == 1 && i < 32) {
	  bez2[bez2c] = temp2[i];
	  bez2c++;
	}
	if((i / 4) % 2 == 0 && i >= 32) {
	  bez3[bez3c] = temp2[i];
	  bez3c++;
	}
	if((i / 4) % 2 == 1 && i >= 32) {
	  bez4[bez4c] = temp2[i];
	  bez4c++;
	}
      }
      
      for(i = 0; i < 16; i++) {
	printf("%d:\n", i);
	point_print(&bez1[i], stdout);
	point_print(&bez2[i], stdout);
	point_print(&bez3[i], stdout);
	point_print(&bez4[i], stdout);
      }

      //printf("HI\n");
      bezierSurface_set(&bezSurfaceA, &bez1[0]);
      bezierSurface_set(&bezSurfaceB, &bez2[0]);
      bezierSurface_set(&bezSurfaceC, &bez3[0]);
      bezierSurface_set(&bezSurfaceD, &bez4[0]);
