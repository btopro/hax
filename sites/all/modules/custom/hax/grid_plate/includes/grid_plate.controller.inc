<?php

/**
 * @file
 * Grid Plate controller class.
 */

/**
 * The Controller for Grid Plate entities.
 */
class GridPlateController extends EntityAPIController {
  /**
   * Create a Grid Plate.
   *
   * @param array $values
   *   An array containing the possible values.
   *
   * @return object
   *   A object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our entity.
    $values += array(
      'grid_plate_id' => '',
      'is_new' => TRUE,
      'label' => '',
    );

    $entity = parent::create($values);

    return $entity;
  }
}
