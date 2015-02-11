<?php

/**
 * @file
 * Hax Element controller class.
 */

/**
 * The Controller for Hax Element entities.
 */
class HaxElementController extends EntityAPIController {
  /**
   * Create a Hax Element.
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
      'hax_element_id' => '',
      'is_new' => TRUE,
      'label' => '',
    );

    $entity = parent::create($values);

    return $entity;
  }
}
