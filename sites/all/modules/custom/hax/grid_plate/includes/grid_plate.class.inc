<?php

/**
 * @file
 * Grid Plate class.
 */

/**
 * The class used for grid_plate entities.
 */
class GridPlate extends Entity {
  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'grid_plate');
  }

  /**
   * Defines the default entity label.
   */
  protected function defaultLabel() {
    return $this->label;
  }

  /**
   * Defines the default entity URI.
   */
  protected function defaultUri() {
    return array('path' => 'grid_plate/' . $this->grid_plate_id);
  }
}

/**
 * The class used for Grid Plate type entities.
 */
class GridPlateType extends Entity {
  public $type;
  public $label;

  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'grid_plate_type');
  }
}
