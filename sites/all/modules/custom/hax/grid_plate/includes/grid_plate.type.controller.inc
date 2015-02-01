<?php

/**
 * @file
 * Grid Plate controller class.
 */

/**
 * The Controller for Grid Plate entities.
 */
class GridPlateTypeController extends EntityAPIControllerExportable {
  /**
   * Create a Grid Plate type.
   *
   * @param array $values
   *   An array containing the possible values.
   *
   * @return object
   *   A type object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Grid Plate.
    $values += array(
      'id' => '',
    );
    $entity_type = parent::create($values);

    return $entity_type;
  }
}
