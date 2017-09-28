import { Component, OnInit } from '@angular/core';
import { Dish } from '../shared/dish';
import {DishService} from '../service/dish.service';
                        
@Component({
  selector: 'app-menu',
  templateUrl: './menu.component.html',
  styleUrls: ['./menu.component.css']
})
export class MenuComponent implements OnInit {

  dishes: Dish[];
  selectedDish: Dish;
  constructor(private dishService: DishService) { }

  ngOnInit() {
    this.dishes=this.dishService.getDishes();
  }

  onSelect(dish: Dish)
  {
    this.selectedDish = dish;
  }
}